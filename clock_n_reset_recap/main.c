#include <msp430.h> 

#define LED BIT7
#define SW0 BIT0
#define SW1 BIT1
#define SW2 BIT2
void register_settings_for_GPIO()
{
    P1DIR |= LED;
    P1DIR &= ~(SW0 + SW1 + SW2);
    P1REN |= (SW0 + SW1 + SW2);
    P1OUT |= (SW0 + SW1 + SW2);
}

void register_settings_for_VLO()
{
    BCSCTL3 |= LFXT1S_0;

    do
    {
        IFG1 &= ~OFIFG;
        __delay_cycles(1000);
    }
    while(IFG1 & OFIFG);

    BCSCTL2 |= SELM_3;
}

void toggle_cpu_frequency()
{
    if(!(P1IN & SW0))
    {
        __delay_cycles(20000);
        while(!(P1IN & SW0))
            ;
        __delay_cycles(20000);
        BCSCTL2 &= ~(BIT5 + BIT4);
    }
    if(!(P1IN & SW1))
    {
        __delay_cycles(20000);
        while(!(P1IN & SW1))
            ;
        __delay_cycles(20000);
        BCSCTL2 &= ~(BIT5 + BIT4);
        BCSCTL2 |= DIVM_1;
    }
    if(!(P1IN & SW2))
    {
        __delay_cycles(20000);
        while(!(P1IN & SW0))
            ;
        __delay_cycles(20000);
        BCSCTL2 &= ~(BIT5 + BIT4);
        BCSCTL2 |= DIVM_2;
    }
}
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	register_settings_for_GPIO();
	register_settings_for_VLO();
	while(1)
	{
	    toggle_cpu_frequency();
	    P1OUT ^= LED;
	    __delay_cycles(10000);
	}
	return 0;
}
