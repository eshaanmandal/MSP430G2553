#include <msp430.h> 

#define LED BIT7
/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= LED;
	while(1)
	{
	    __delay_cycles(1000000);
	    P1OUT ^= LED;
	}
	return 0;
}
