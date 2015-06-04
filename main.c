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
//#include <msp430g2553.h>
#include <msp430g2452.h>

// board (leds)
#define LED_INIT() {P1DIR|=0x41;P1OUT&=~0x41;}
#define LED_RED_ON() {P1OUT|=0x01;}
#define LED_RED_OFF() {P1OUT&=~0x01;}
#define LED_RED_SWAP() {P1OUT^=0x01;}
#define LED_GREEN_ON() {P1OUT|=0x40;}
#define LED_GREEN_OFF() {P1OUT&=~0x40;}
#define LED_GREEN_SWAP() {P1OUT^=0x40;}

#define BUTTON BIT3
#define BTN_DOWN ((P1IN&BIT3)==0)

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

#define RTC_SAMPLING_FREQV 1024

#define TOTAL_TICKS_25M 6000
#define TOTAL_TICKS_5M 1200
//test
//#define TOTAL_TICKS_25M 300
//#define TOTAL_TICKS_5M 120

volatile unsigned int leds[LEDS_NUM] = {0,0,0,0,0,0,0};
unsigned int pleds[LEDS_NUM] = {0,0,0,0,0,0,0};

void setonepwm(unsigned char which, unsigned char how)
{
    if ((which>=0)&&(which<LEDS_NUM))
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
    P1DIR&=~BUTTON; /*P1IE|=BUTTON; P1IES|=BUTTON; P1IFG&=~BUTTON;*/ P1REN|=BUTTON;

	LED_INIT(); // leds
	LEDS_INIT();
}

#define SEQV_RESET 0
#define SEQV_25M 10
#define SEQV_5M 20

// main program body
int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;	// Stop WDT

	board_init(); // init dco and leds
	rtc_timer_init(); // init 32kHz clock timer

    int seqv = SEQV_RESET; // sequential pointer
    unsigned int tcnt=0; // timer counter
    int ptr=0; // led pointer

    int i;

	while(1)
	{
        __bis_SR_register(CPUOFF + GIE); // enter sleep mode
        // it weaks 4times per second by rtc timer
        switch (seqv)
        {
            case SEQV_RESET:
                for (i=0;i<LEDS_NUM;i++) leds[i]=0;
                seqv++;
                break;
            case (SEQV_RESET+1): // wait button
                if (BTN_DOWN)
                {
                    for (i=0;i<LEDS_NUM;i++) leds[i]=0x10;
                    seqv++;
                }
                break;
            case (SEQV_RESET+2):
                if (!BTN_DOWN) seqv=SEQV_25M;
                break;

            case SEQV_25M: // init 25min timer
                tcnt=0;
                for (i=0;i<LEDS_NUM;i++) leds[i]=0;
                ptr=0;
                leds[ptr]=0x10;
                seqv++;
                break;
            case (SEQV_25M+1): // 25min ticking
                if ((tcnt&0x07)==0) leds[ptr]=0x10;
                else if ((tcnt&0x07)==3)
                {
                    if (tcnt>=((TOTAL_TICKS_25M/LEDS_NUM)*(ptr+1))) ptr++;
                    if (ptr>=LEDS_NUM) seqv++;
                    else leds[ptr]=0x00;
                }
                if (BTN_DOWN)
                {
                    for (i=0;i<LEDS_NUM;i++) leds[i]=0x10;
                    seqv+=2;
                }
                break;
            case (SEQV_25M+2): // 25m passed
                if (BTN_DOWN) seqv++;
                break;
            case (SEQV_25M+3):
                if (!BTN_DOWN) seqv=SEQV_5M;
                break;

            case SEQV_5M: // init 5min timer
                tcnt=0;
                for (i=0;i<LEDS_NUM;i++) leds[i]=0x10;
                ptr=0;
                leds[ptr]=0;
                seqv++;
                break;
            case (SEQV_5M+1): // 5min ticking
                if ((tcnt&0x03)==0) leds[ptr]=0;
                else if ((tcnt&0x03)==2)
                {
                    if (tcnt>=((TOTAL_TICKS_5M/LEDS_NUM)*(ptr+1))) ptr++;
                    if (ptr>=LEDS_NUM) seqv++;
                    else leds[ptr]=0x10;
                }
                if (BTN_DOWN)
                {
                    for (i=0;i<LEDS_NUM;i++) leds[i]=0x00;
                    seqv+=2;
                }
                break;
            case (SEQV_5M+2): // 25m passed
                if (BTN_DOWN) seqv++;
                break;
            case (SEQV_5M+3):
                if (!BTN_DOWN) seqv=SEQV_25M;
                break;

            default:
                seqv = SEQV_RESET;
                break;
        }
        tcnt++;
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

    // every 1/4s leave powersave
    if (rtc_div==0) __bic_SR_register_on_exit(CPUOFF);  // Clear CPUOFF bit from 0(SR)

    // dimming and pwm output
    for (i=0;i<LEDS_NUM;i++)
    {
        setoneonoff(i,(pleds[i]>(rtc_div&0x0F))?1:0);
    }

    if ((rtc_div&0x0F)==0)
    {
        for (i=0;i<LEDS_NUM;i++)
        {
            if (pleds[i]>leds[i]) pleds[i]--;
            if (pleds[i]<leds[i]) pleds[i]++;
        }
    }

    // increase time divider
    rtc_div++;
}
