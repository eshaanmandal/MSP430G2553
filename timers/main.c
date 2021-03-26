#include<msp430.h>
#define LED BIT7
void register_setting_GPIO()
{
    P1DIR |= LED;
}
void register_setting_Timer()
{
    TACCTL0 = CCIE;
    TACTL = MC_1 + TASSEL_1;
    TACCR0 =  4096;
}
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // disable Watch dog timer
    register_setting_GPIO();
    register_setting_Timer();
    do
    {
        IFG1 &= ~OFIFG;
        __delay_cycles(50000);
    }
    while(IFG1 & OFIFG);
    __bis_SR_register(GIE + LPM3_bits);
    return 0;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer_for_led(void)
{
    P1OUT ^= LED;
}
