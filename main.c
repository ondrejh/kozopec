//******************************************************************************
// Pomodoro timer for MSP430 launchpad
//
//
// author:          Ondrej Hejda
// date (started):  28.2.2013
//
// hardware: MSP430G2553 (launchpad)
//
//                MSP4302553
//             -----------------
//         /|\|                 |
//          | |             XTAL|<---> 32.768kHz quartz (realtime clock)
//          --|RST              |
//            |             P1.3|<---- BUTTON
//            |                 |
//            |             P2.1|----> LED1
//            |             P2.0|----> LED2
//            |             P1.5|----> LED3
//            |             P1.4|----> LED4
//            |             P1.3|----> LED5
//            |             P2.5|----> LED6
//            |             P2.4|----> LED7
//            |                 |
//
//******************************************************************************

// include section
#include <msp430g2553.h>
//#include <msp430g2452.h>
#include <stdint.h>

// onboard leds
#define LED_INIT() do{P1DIR|=0x41;P1OUT&=~0x41;}while(0)
#define LED_RED_ON() do{P1OUT|=0x01;}while(0)
#define LED_RED_OFF() do{P1OUT&=~0x01;}while(0)
#define LED_RED_SWAP() do{P1OUT^=0x01;}while(0)
#define LED_GREEN_ON() do{P1OUT|=0x40;}while(0)
#define LED_GREEN_OFF() do{P1OUT&=~0x40;}while(0)
#define LED_GREEN_SWAP() do{P1OUT^=0x40;}while(0)

// onboard button
#define BUTTON_INIT() do{P1DIR&=~BIT3;P1REN|=BIT3;}while(0)
#define BUTTON ((P1IN&BIT3)==0)

// motor outputs
#define MOTOR_INIT() do{P1DIR|0x01;P1OUT&=~0x01;P2DIR|=0x06;P2OUT&=~06;}while(0)
//#define MOTOR_DIR(x) do{(x)?(P2OUT|=0x02):(P2OUT&=~0x02)}while(0)
#define MOTOR_STEP() do{P2OUT^=0x04;}while(0)
#define MOTOR_ENABLE() do{P1OUT|=0x01;}while(0)
#define MOTOR_DISABLE() do{P1OUT&=~0x01;}while(0)

#define STEP_DIV 500 // 2000Hz / 1MHz
#define STEP_OVF 1000
#define STEP_ACC 2

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

	// free running timer
	TACCR0 = 0xFFFF;
	TACTL = TASSEL_2 + MC_1; // SMCLK, upmode
}

// main program body
int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;	// Stop WDT

	board_init(); // init hw

	while(1)
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
            mv += ma;
	    }

	    // system sequential
        static int seqv = 0;
        switch (seqv) {
        case 0: // wait button
            if (BUTTON) {
                MOTOR_ENABLE();
                mv = 0;
                ma = STEP_ACC;
                seqv++;
            }
            break;
        case 1: // acceleration (wait button release)
            if (mv >= STEP_OVF)
                mv = STEP_OVF-1;
            if (!BUTTON) {
                ma = -STEP_ACC;
                seqv++;
            }
            break;
        case 2: // deceleration (wait button)
            if (BUTTON) {
                ma = STEP_ACC;
                seqv--;
            }
            else if (mv < 0) {
                mv = 0;
                MOTOR_DISABLE();
                seqv = 0;
            }
            break;
        }
	}

	return -1;
}
