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

// board (leds)
#define LED_INIT() {P1DIR|=0x41;P1OUT&=~0x41;}
#define LED_RED_ON() {P1OUT|=0x01;}
#define LED_RED_OFF() {P1OUT&=~0x01;}
#define LED_RED_SWAP() {P1OUT^=0x01;}
#define LED_GREEN_ON() {P1OUT|=0x40;}
#define LED_GREEN_OFF() {P1OUT&=~0x40;}
#define LED_GREEN_SWAP() {P1OUT^=0x40;}

#define BUTTON BIT3

#define LEDS_INIT() do{P2DIR|=0x37;P2OUT&=~0x37;P1DIR|=0x30;P1OUT&=~0x30;}while(0)
#define LED1_ON() do{P2OUT|=0x02;}while(0)
#define LED1_OFF() do{P2OUT&=~0x02;}while(0)
#define LED1_SWAP() do{P2OUT^=0x02;}while(0)
#define LED2_ON() do{P2OUT|=0x01;}while(0)
#define LED2_OFF() do{P2OUT&=~0x01;}while(0)
#define LED2_SWAP() do{P2OUT^=0x01;}while(0)
#define LED3_ON() do{P1OUT|=0x20;}while(0)
#define LED3_OFF() do{P1OUT&=~0x20;}while(0)
#define LED3_SWAP() do{P1OUT^=0x20;}while(0)
#define LED4_ON() do{P1OUT|=0x10;}while(0)
#define LED4_OFF() do{P1OUT&=~0x10;}while(0)
#define LED4_SWAP() do{P1OUT^=0x10;}while(0)
#define LED5_ON() do{P2OUT|=0x04;}while(0)
#define LED5_OFF() do{P2OUT&=~0x04;}while(0)
#define LED5_SWAP() do{P2OUT^=0x04;}while(0)
#define LED6_ON() do{P2OUT|=0x20;}while(0)
#define LED6_OFF() do{P2OUT&=~0x20;}while(0)
#define LED6_SWAP() do{P2OUT^=0x20;}while(0)
#define LED7_ON() do{P2OUT|=0x10;}while(0)
#define LED7_OFF() do{P2OUT&=~0x10;}while(0)
#define LED7_SWAP() do{P2OUT^=0x10;}while(0)

#define LEDS_NUM 7

#define RTC_SAMPLING_FREQV 512

unsigned char leds[LEDS_NUM] = {0,0,0,0,0,0,0};

void setonepwm(unsigned char which, unsigned char how)
{
    if ((which>0)&&(which<=LEDS_NUM))
    {
        leds[which]=how;
    }
}

void setoneonoff(unsigned char which, unsigned char how)
{
    if (how!=0)
    {
        switch(which)
        {
            case 0: LED1_ON();  break;
            case 1: LED2_ON();  break;
            case 2: LED3_ON();  break;
            case 3: LED4_ON();  break;
            case 4: LED5_ON();  break;
            case 5: LED6_ON();  break;
            case 6: LED7_ON();  break;
        }
    }
    else
    {
        switch(which)
        {
            case 0: LED1_OFF(); break;
            case 1: LED2_OFF(); break;
            case 2: LED3_OFF(); break;
            case 3: LED4_OFF(); break;
            case 4: LED5_OFF(); break;
            case 5: LED6_OFF(); break;
            case 6: LED7_OFF(); break;
        }
    }
}

/*void swapone(unsigned char which)
{
    switch (which)
    {
        case 1:
            LED1_SWAP();
            break;
        case 2:
            LED2_SWAP();
            break;
        case 3:
            LED3_SWAP();
            break;
        case 4:
            LED4_SWAP();
            break;
        case 5:
            LED5_SWAP();
            break;
        case 6:
            LED6_SWAP();
            break;
        case 7:
            LED7_SWAP();
            break;
        default:
            break;
    }
}*/

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
	LEDS_INIT();
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
    static unsigned char rtc_div = 0;

    unsigned char i;

    // every 1/8s
    if ((rtc_div&0x3F)==0)
    {
        static unsigned char which = 0;
        setonepwm(which++,16);
        if (which==LEDS_NUM) which=0;
    }

    // dimming and pwm output
    for (i=0;i<LEDS_NUM;i++)
    {
        setoneonoff(i,(leds[i]>(rtc_div&0x0F))?1:0);
        if (leds[i]>0) leds[i]--;
    }

    // increase time divider
    rtc_div++;
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    // button input
    if (P1IFG&BUTTON)
    {
        P1IFG &= ~BUTTON; // P1.3 IFG cleared
        //LED_RED_SWAP();
        LED1_SWAP();
    }
}
