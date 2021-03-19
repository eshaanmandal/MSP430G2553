#include <msp430.h> 

#define LED BIT7
#define SW3 BIT3
#define SW4 BIT4
void register_setting_GPIO();
void register_setting_VLO();
void switch_input();
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	register_setting_GPIO(); // Initializing the input pins
	register_setting_VLO();
	while(1)
	{
	    switch_input();
	    P1OUT ^= LED;
	    __delay_cycles(2000);
	}
	return 0;
}
void register_setting_GPIO()
{
    P1DIR |= LED; // Means led would be used as output
    P1DIR &= ~(SW3+SW4); // Switch connected to Pin 1.3 and Pin 1.4 would take input from user
    /*
     * Setting up the Resistors
     * They should be pull-up
     */
    P1REN |= (SW3 + SW4); // Resistors enabled
    P1OUT |= (SW3 + SW4); //Type : Pull up
}
void register_setting_VLO()
{
    /*
     * We would initialize thr VLO but it is unstable in the beginning so
     * we have to wait until it becomes stable
     */
    BCSCTL3 |= LFXT1S_2; // VLO assigned as LFX clk
    do
    {
        IFG1 &= ~OFIFG;
        __delay_cycles(50000);
    }
    while(IFG1 & OFIFG);
    BCSCTL2 |= (BIT7 + BIT6);
}
void switch_input()
{
    if(!(P1IN & SW3))
    {
        __delay_cycles(2000);
        while(!(P1IN & SW3));
        __delay_cycles(2000);
       BCSCTL2 &= ~(BIT5+BIT4); // clear the divider flags
       BCSCTL2 |= DIVM_3; // clk/4
    }
    if(!(P1IN & SW4))
    {
        __delay_cycles(2000);
        while(!(P1IN & SW4));
        __delay_cycles(2000);
       BCSCTL2 &= ~(BIT5+BIT4); // clear the divider flags
       BCSCTL2 |= DIVM_2;
    }

}
