//******************************************************************************
// Simple stepper driver with MSP430 mcu
//
//
// author:          Ondrej Hejda
// date (started):  26.6.2020
//
// hardware: MSP430G2553 / MSP430G2452
//
//                MSP4302553
//             -----------------
//         /|\|                 |
//          | |             P1.2|<---- BACKWARD
//          --|RST          P1.3|<---- FORWARD
//            |             P1.4|<---- RELEASE
//            |                 |
//            |             P1.5|<---- SPEED (analog 0 .. 3.3V)
//            |                 |
//            |             P1.0|----> ENABLE
//            |             P1.1|----> STEP
//            |             P1.6|----> DIRRECTION
//            |                 |
//
//******************************************************************************

// include section
//#include <msp430g2553.h>
//#include <msp430g2452.h>
#include <msp430g2231.h>

#include <stdint.h>

// on-board leds
#define LED_INIT() do{P1DIR|=0x41;P1OUT&=~0x41;}while(0)
#define LED_RED_ON() do{P1OUT|=0x01;}while(0)
#define LED_RED_OFF() do{P1OUT&=~0x01;}while(0)
#define LED_RED_SWAP() do{P1OUT^=0x01;}while(0)
#define LED_GREEN_ON() do{P1OUT|=0x40;}while(0)
#define LED_GREEN_OFF() do{P1OUT&=~0x40;}while(0)
#define LED_GREEN_SWAP() do{P1OUT^=0x40;}while(0)

// on-board button
#define BUTTON_INIT() do{P1DIR&=~BIT3;P1REN|=BIT3;}while(0)
#define BUTTON ((P1IN&BIT3)==0)

// inputs (button with pull-up, active low)
#define INPUT_INIT() do{P1DIR|=0x1C;P1REN|=0x1C;}while(0)
#define FORWARD ((P1IN&BIT3)==0)
#define BACKWARD ((P1IN&BIT2)==0)
#define RELEASE ((P1IN&BIT4)==0)

// motor outputs (opto-coupled outputs, active low)
#define MOTOR_INIT() do{P1DIR|0x01;P1OUT&=~0x01;P2DIR|=0x06;P2OUT&=~06;}while(0)
#define MOTOR_DIR(x) do{(x)?(P2OUT|=0x02):(P2OUT&=~0x02);}while(0)
#define FORW 0
#define BACK 1
#define DIR_FORW ((P2OUT&0x02)==0)
#define DIR_BACK ((P2OUT&0x02)!=0)
#define MOTOR_STEP() do{P2OUT^=0x04;}while(0)
#define MOTOR_ENABLE() do{P1OUT|=0x01;}while(0)
#define MOTOR_DISABLE() do{P1OUT&=~0x01;}while(0)
#define MOTOR_ENABLED (P1OUT&0x01)

#define STEP_DIV 500 // 2000Hz / 1MHz
#define STEP_OVF 1000
#define STEP_ACC 20
#define SPEED_CNT_DIV 10

// leds and dco init
void board_init(void)
{
	// oscillator
	BCSCTL1 = CALBC1_1MHZ; // Set DCO
	DCOCTL = CALDCO_1MHZ;

    // button
    BUTTON_INIT();

    // leds
	LED_INIT();

	// motor
	MOTOR_INIT();

	// inputs
	INPUT_INIT();

	// free running timer
	TACCR0 = 0xFFFF;
	TACTL = TASSEL_2 + MC_1; // SMCLK, upmode
}

// main program body
int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;	// Stop WDT

	board_init(); // init hw

	while(1) // main loop
	{
	    // motor step control
	    static uint16_t mt = 0;
	    static uint16_t mp = 0; // step period
	    static int16_t mv = 50; // step speed, if 0 stop
	    static int16_t ma = 0;
        if ((TAR - mt) > STEP_DIV) {
            if (mv!=0) {
                mt += STEP_DIV;
                mp += mv;
                if (mp > STEP_OVF) {
                    mp -= STEP_OVF;
                    MOTOR_STEP();
                    LED_GREEN_SWAP();
                }
            }
            else {
                mt = TAR;
                mp = 0;
            }
            // speed control
            static int div = 0;
            div ++;
            if (div == SPEED_CNT_DIV) {
                mv += ma;
                div = 0;
            }
	    }

	    // system sequential
        static int seqv = 0;
        switch (seqv) {
        case 0: // wait button
            if (FORWARD) {
                MOTOR_DIR(0);
                MOTOR_ENABLE();
                mv = 0;
                ma = STEP_ACC;
                seqv++;
            }
            else if (BACKWARD) {
                MOTOR_DIR(1);
                MOTOR_ENABLE();
                mv = 0;
                ma = STEP_ACC;
                seqv++;
            }
            else if (RELEASE && MOTOR_ENABLED)
                MOTOR_DISABLE();
            break;
        case 1: // acceleration (wait button release)
            if (mv >= STEP_OVF)
                mv = STEP_OVF-1;
            if ((DIR_FORW && (!FORWARD)) || (DIR_BACK && (!BACKWARD))) {
                ma = -STEP_ACC;
                seqv++;
            }
            break;
        case 2: // deceleration (wait button)
            if ((DIR_FORW && FORWARD) || (DIR_BACK && (!BACKWARD))) {
                ma = STEP_ACC;
                seqv--;
            }
            else if (mv <= 0) {
                mv = 0;
                seqv = 0;
            }
            break;
        }
	}

	return -1;
}
