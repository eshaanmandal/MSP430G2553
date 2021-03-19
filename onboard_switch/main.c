#include <msp430.h> 


/**
 * We are going to use the on-board switch and led(MSP430Lunchbox)
 * The led is connected to pin 1.7
 * The switch is connected to pin 1.3
 */
#define LED BIT7
#define SWITCH BIT3
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= LED; //setting the LED pin as output
	P1DIR &= ~SWITCH; //setting the switch pin as input
	// By default this uses a pull up resistor
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
