#include <msp430.h> 

#define LED BIT7  // for the on-board LED connected to pin 1.7
#define SW1 BIT1  // for the switch connected to pin 1.1 using a pull-up resistor
#define SW2 BIT2  // for the switch connected to pin 1.2 using a pull-up resistor
#define SW3 BIT3  // for the switch connected to pin 1.3 using a pull-up resistor
volatile unsigned int i;
void register_setting_pins()
{
    P1DIR |= LED;
    P1DIR &= ~(SW1 + SW2 + SW3);
    P1REN |= (SW1 + SW2 + SW3);
    P1OUT |= (SW1 + SW2 + SW3);
    P1IES &= ~(SW1 + SW2 + SW3);
    P1IE |= (SW1 + SW2 + SW3);
    __bis_SR_register(GIE);
}
void register_setting_VLO()
{
    BCSCTL3 |= (BIT5 + ~BIT4);
    do
    {
        IFG1 &= ~OFIFG;
        for(i=50000;i;--i)
            ;
    }
    while(IFG1 & OFIFG);
    BCSCTL2 |= (BIT7 + BIT6);
}
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	/*
	 * 1.Initializing all the pins
	 */
	register_setting_pins();
	register_setting_VLO();
	while(1)
	{
	    P1OUT ^= LED;
	    __delay_cycles(2000);
	}
	return 0;
}
#pragma vector=PORT1_VECTOR
__interrupt void freq_chng(void)
{
    if(P1IFG & SW1)
    {
        BCSCTL2 &= ~(BIT5 + BIT4); //clear the divider
        BCSCTL2 |= (BIT5 + BIT4); // divide by 8
        __delay_cycles(20000);
        P1IFG &= ~SW1;
    }
    else if(P1IFG & SW2)
    {
        BCSCTL2 &= ~(BIT5 + BIT4); //clear the divider
        BCSCTL2 |= (BIT5 + ~BIT4); // divide by 4
        __delay_cycles(20000);
        P1IFG &= ~SW2;
    }
    else if(P1IFG & SW3)
    {
        BCSCTL2 &= ~(BIT5 + BIT4); //clear the divider
        BCSCTL2 |= (~BIT5 + BIT4); // divide by 2
        __delay_cycles(20000);
        P1IFG &= ~SW3;
    }

}
