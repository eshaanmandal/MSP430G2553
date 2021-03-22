#include <msp430.h> 

#define LED BIT7
#define SW BIT4
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= LED;
	P2DIR &= ~SW;
	P2REN |= SW;
	P2OUT |= SW;
	P2IES &= ~SW;
	P2IE |= SW;

	__bis_SR_register(GIE);
	while(1)
	    ;
}
#pragma vector=PORT2_VECTOR
__interrupt void port1_itrupt(void)
{
   if(P2IFG & SW)
   {
       P1OUT ^= LED;
       __delay_cycles(20000);
       P2IFG &= ~SW;
   }
}
