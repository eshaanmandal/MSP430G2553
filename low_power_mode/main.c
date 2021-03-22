#include <msp430.h> 


#define LED BIT7
#define SW BIT3
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= LED; //Pin 1.7 as output
	P1OUT &= ~LED; // turn off the LED

	P1DIR &= ~SW; //Pin 1.3 as input
    //enabling the interrupts
	P1IES &= ~SW;
	P1IE |= SW;

	unsigned int i;
	while(1)
	{
	    __bis_SR_register(LPM4_bits + GIE);
	    for(i=200000;i;--i)
	               ;
	    P1OUT ^= LED;
	}
	return 0;
}
#pragma vector=PORT1_VECTOR
__interrupt void port_1(void)
{
    __bic_SR_register_on_exit(LPM4_bits + GIE);
    P1IFG &= ~SW;
}
