#include <msp430.h> 

#define LED BIT7 // internal led connected to pi 1.7
#define SWITCH BIT4 //external switch connected to pin 1.4
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= LED;
	P1DIR &= ~SWITCH;
	P1REN |= SWITCH; // enabling the resistor
	/*
	 * For pull up P1OUT |= SWICTH;
	 * For pull down P1OUT &= ~SWITCH;
	 */
	P1OUT |= SWITCH;
	while(1)
	{
	    if(!(P1IN & SWITCH))
	    {
	        __delay_cycles(20000);
	        while(!(P1IN & SWITCH))
	            ;
	        __delay_cycles(20000);
	        P1OUT ^= LED;
	    }
	}
	return 0;
}
