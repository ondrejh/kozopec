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
#include <stdbool.h>

#define BTN_PUSH 100
#define BTN_HOLD 1000

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
#define INPUT_INIT() do{P1DIR&=~0x1C;P1REN|=0x1C;}while(0)
#define FORWARD ((P1IN&BIT3)==0)
#define BACKWARD ((P1IN&BIT2)==0)
#define RELEASE ((P1IN&BIT4)!=0)

// motor outputs (opto-coupled outputs, active low)
#define MOTOR_INIT() do{P1DIR|=0x43;P1OUT&=~43;}while(0)
#define MOTOR_DIR(x) do{(x)?(P1OUT|=BIT6):(P1OUT&=~BIT6);}while(0)
#define FORW 0
#define BACK 1
#define DIR_FORW ((P1OUT&BIT6)!=0)
#define DIR_BACK ((P1OUT&BIT6)==0)
#define MOTOR_STEP() do{P1OUT^=BIT1;}while(0)
#define MOTOR_ENABLE() do{P1OUT|=BIT0;}while(0)
#define MOTOR_DISABLE() do{P1OUT&=~BIT0;}while(0)
#define MOTOR_ENABLED ((P1OUT&BIT0)==0)

#define STEP_DIV 200 // 5000Hz / 1MHz
#define STEP_OVF 1500
#define STEP_ACC 5
#define MAX_SPEED 500

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

	// analog input
	P1DIR &= ~BIT5; P1SEL |= BIT5;
	ADC10CTL1 = INCH_5 + ADC10DIV_3 ;         // Channel 3, ADC10CLK/3
	ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON;
    //ADC10CTL0 = ADC10SHT_2 + ADC10ON; // ADC10ON, interrupt enabled
    //ADC10CTL1 = INCH_5;               // input A5
    ADC10AE0 |= BIT5;                 // PA.5 ADC option select
    ADC10CTL0 |= ENC + ADC10SC;       // start conversion

	// free running timer
	TACCR0 = 0xFFFF;
	TACTL = TASSEL_2 + MC_1; // SMCLK, upmode
}

// main program body
int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;	// Stop WDT

	board_init(); // init hw

	enum {
	    MOD_STOP = 0,
	    MOD_FWD_PUSH,
	    MOD_FWD_HOLD,
	    MOD_BWD_PUSH,
	    MOD_BWD_HOLD,
	} mode = MOD_STOP;

	while(1) // main loop
	{
	    // motor step control
	    static uint16_t mt = 0;
	    static uint16_t mp = 0; // step period
	    static int16_t mv = 0; // step speed, if 0 stop
	    static int16_t ma = 0;
	    static int16_t max_speed = 200;
	    bool fwd_push = false, bwd_push = false;
	    static bool fwd_hold = false, bwd_hold = false, rel_hold = false;
        if ((TAR - mt) > STEP_DIV) {
            if (mv!=0) {
                mt += STEP_DIV;
                mp += mv;
                if (mp > STEP_OVF) {
                    mp -= STEP_OVF;
                    MOTOR_STEP();
                }
            }
            else {
                mt = TAR;
                mp = 0;
            }
            // speed control
            static int cnt = 0;
            if (cnt==10) {
                mv += ma;
                if (mv >= max_speed) mv = max_speed;
                if (mv < 0) mv = 0;
                cnt = 0;
            }
            cnt ++;

            static int adc_cnt = 0;
            if (adc_cnt >= 500) {
                adc_cnt = 0;
                max_speed = ADC10MEM + 200;
                ADC10CTL0 |= ENC + ADC10SC;
            }
            adc_cnt++;

    	    static uint16_t btn_fwd = 0, btn_bwd = 0, btn_rel = 0;
	        static bool fwd_stat = false, bwd_stat = false;

	        // button filtering
            if (FORWARD) {
                if (btn_fwd < BTN_HOLD) {
                    btn_fwd ++;
                    if (btn_fwd >= BTN_PUSH)
                        fwd_stat = true;
                } else
                    fwd_hold = true;
            } else {
                if (btn_fwd > BTN_PUSH) {
                    btn_fwd = BTN_PUSH;
                    if (fwd_stat == true)
                        fwd_push = true;
                } else if (btn_fwd > 0)
                    btn_fwd --;
                else {
                    fwd_stat = false;
                    fwd_hold = false;
                }
            }

            if (BACKWARD) {
                if (btn_bwd < BTN_HOLD) {
                    btn_bwd ++;
                    if (btn_bwd >= BTN_PUSH)
                        bwd_stat = true;
                } else
                    bwd_hold = true;
            } else {
                if (btn_bwd > BTN_PUSH) {
                    btn_bwd = BTN_PUSH;
                    if (bwd_stat == true)
                        bwd_push = true;
                } else if (btn_bwd > 0)
                    btn_bwd --;
                else {
                    bwd_stat = false;
                    bwd_hold = false;
                }
            }

            if (RELEASE) {
                if (btn_rel < BTN_PUSH)
                    btn_rel ++;
                else
                    rel_hold = true;
            } else {
                if (btn_rel > 0)
                    btn_rel --;
                else
                    rel_hold = false;
            }
	    }

	    // system sequential
        static int seqv = 0;
        switch (seqv) {
        case 0: // wait button
            mode = MOD_STOP;
            if (fwd_push)
                mode = MOD_FWD_PUSH;
            if (bwd_push)
                mode = MOD_BWD_PUSH;
            if (fwd_hold)
                mode = MOD_FWD_HOLD;
            if (bwd_hold)
                mode = MOD_BWD_HOLD;

            if (mode != MOD_STOP) {
                if ((mode == MOD_FWD_PUSH) || (mode == MOD_FWD_HOLD))
                    MOTOR_DIR(1);
                else
                    MOTOR_DIR(0);
                MOTOR_ENABLE();
                mv = 0;
                ma = STEP_ACC;
                seqv++;
            }
            else {
                if (rel_hold)
                    MOTOR_DISABLE();
                else
                    MOTOR_ENABLE();
            }
            break;
        case 1: // acceleration, wait stop event (depends on mode)
            if ((((mode == MOD_FWD_PUSH) || (mode == MOD_BWD_PUSH)) && (fwd_push || bwd_push))
                || ((mode == MOD_FWD_HOLD) && (!fwd_hold))
                || ((mode == MOD_BWD_HOLD) && (!bwd_hold))) {
                ma = -STEP_ACC;
                seqv++;
            }
            break;
        case 2: // deceleration
            if (mv <= 0) {
                mv = 0;
                ma = 0;
                seqv = 0;
            }
            break;
        }
	}

	return -1;
}
