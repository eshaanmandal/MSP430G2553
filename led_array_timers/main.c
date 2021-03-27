#include <msp430.h> 
#include<inttypes.h>
volatile unsigned int i;
volatile char led=0;
void register_settings_GPIO()
{
    P1DIR |= 0xFF;
    P1OUT |= 0x00;
}
void register_settings_timer()
{
    TACCTL0 = CCIE;
    TACTL = MC_1 + TASSEL_1;
    TACCR0 = 32768;
}
void setup_ACLK()
{
    do
    {
        IFG1 &= ~OFIFG;
        __delay_cycles(50000);
    }
    while(IFG1 & OFIFG);
}
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	register_settings_GPIO();
	setup_ACLK();
	register_settings_timer();
	__bis_SR_register(GIE + LPM3_bits);
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void leds(void)
{
    P1OUT = led++;
}
