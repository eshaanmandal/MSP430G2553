#include <msp430.h> 

#define LED BIT7
#define SWITCH BIT2
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= LED;
	P1DIR &= ~SWITCH;
	P1REN |= SWITCH;
	P1OUT &= ~SWITCH;

	while(1)
	{
	    if(P1IN & SWITCH)
	    {
	        __delay_cycles(20000);
	        while(P1IN & SWITCH)
	            ;
	        __delay_cycles(20000);
	        P1OUT ^= LED;
	    }
	}
	return 0;
}

