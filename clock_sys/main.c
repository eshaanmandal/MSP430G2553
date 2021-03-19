#include <msp430.h> 

#define SW3 BIT3
#define SW4 BIT4
#define SW5 BIT5
#define LED BIT7
volatile unsigned int i;
void register_setting_GPIO();
void register_setting_VLO();
void switch_input();
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	register_setting_GPIO();
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
    P1DIR |= LED; //Pin 1.7 set as output
    P1DIR &= ~(SW3 + SW4 + SW5); // Pin 1.3 1.4 1.5 set as input
    P1REN |= (SW3 + SW4 + SW5); // Pin 1.3 1.4 1.5 resistors enabled
    P1OUT |= (SW3 + SW4 + SW5); // Pin 1.3 1.4 1.5 pull up resistor set
}
void register_setting_VLO()
{
    BCSCTL3 |= LFXT1S_2; // LFXT <--- VLO
    do
    {
        IFG1 &= ~OFIFG;
        __delay_cycles(50000);
    }
    while(IFG1 & OFIFG);
    BCSCTL2 |= SELM_3;
}
void switch_input()
{
    if(!(SW3 & P1IN))
    {
        __delay_cycles(2000);
        while(!(SW3 & P1IN));
        __delay_cycles(2000);
        BCSCTL2 &= ~(BIT4 + BIT5); //VLO /1
    }
    else if(!(SW4 & P1IN))
    {
        __delay_cycles(2000);
        while(!(SW4 & P1IN));
        __delay_cycles(2000);
        BCSCTL2 &= ~(BIT4 + BIT5);
        BCSCTL2 |= BIT5; //VLO /4
    }
    else if(!(SW5 & P1IN))
    {
        __delay_cycles(2000);
       while(!(SW5 & P1IN));
       __delay_cycles(2000);
       BCSCTL2 &= ~(BIT4 + BIT5);
       BCSCTL2 |= (BIT4 + BIT5); //VLO/8
    }
}
