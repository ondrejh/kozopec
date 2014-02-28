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
//            |             P1.0|----> LED
//            |                 |
//
//******************************************************************************

// include section
#include <msp430g2553.h>

// board (leds)
#define LED_INIT() {P1DIR|=0x41;P1OUT&=~0x41;}
#define LED_RED_ON() {P1OUT|=0x01;}
#define LED_RED_OFF() {P1OUT&=~0x01;}
#define LED_RED_SWAP() {P1OUT^=0x01;}
#define LED_GREEN_ON() {P1OUT|=0x40;}
#define LED_GREEN_OFF() {P1OUT&=~0x40;}
#define LED_GREEN_SWAP() {P1OUT^=0x40;}

#define BUTTON BIT3

// init rtc timer (32kHz Xtal)
void rtc_timer_init(void)
{
	CCTL0 = CCIE; // CCR0 interrupt enabled
	#ifdef RTC_SAMPLING_FREQV
	CCR0 = (32768/8/RTC_SAMPLING_FREQV)-1;
	#else
	//CCR0 = 511;	  // f = 32768 / 8(ID_3) / 512(CCR0+1) = 8Hz
	CCR0 = 1023;	  // f = 32768 / 8(ID_3) / 1024(CCR0+1) = 4Hz
	//CCR0 = 2047;	  // f = 32768 / 8(ID_3) / 2048(CCR0+1) = 2Hz
	#endif
	TACTL = TASSEL_1 + ID_3 + MC_1; // ACLK, /8, upmode
}

// leds and dco init
void board_init(void)
{
	// oscillator
	BCSCTL1 = CALBC1_1MHZ;		// Set DCO
	DCOCTL = CALDCO_1MHZ;

    // button P1.3
    P1DIR&=~BUTTON; P1IE|=BUTTON; P1IES|=BUTTON; P1IFG&=~BUTTON; P1REN|=BUTTON;

	LED_INIT(); // leds
}

// main program body
int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;	// Stop WDT

	board_init(); // init dco and leds
	rtc_timer_init(); // init 32kHz clock timer

	while(1)
	{
        __bis_SR_register(CPUOFF + GIE); // enter sleep mode (leave on rtc second event)
	}

	return -1;
}

/** interrupt section **/

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    LED_GREEN_SWAP();
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    // button input
    if (P1IFG&BUTTON)
    {
        P1IFG &= ~BUTTON; // P1.3 IFG cleared
        LED_RED_SWAP();
    }
}
