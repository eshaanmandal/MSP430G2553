#include <msp430.h>
#include<inttypes.h>
volatile unsigned int i;
int add =1;
volatile unsigned char led=0;
void register_settings_GPIO()
{
    P1DIR |= 0xFF;
    P1OUT |= 0x00;
    P2REN |= (BIT0 + BIT1);
    P2OUT |= (BIT0 + BIT1);

    //enable interrupts
    P2IE |= (BIT0 + BIT1);
    P2IES &= (~BIT0 + ~BIT1);
}
void register_settings_timer()
{
    TACCTL0 = CCIE;
    TACTL = MC_1 + TASSEL_1;
    TACCR0 = 8192;
}
void setup_ACLK()
{
    do
    {
        IFG1 &= ~OFIFG;
        __delay_cycles(50000);
    }
    while(IFG1 & OFIFG);
}
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    register_settings_GPIO();
    setup_ACLK();
    register_settings_timer();
    __bis_SR_register(GIE + LPM3_bits);
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void leds(void)
{
    led = led + add;
    P1OUT = led;
}

#pragma vector=PORT2_VECTOR
__interrupt void updown(void)
{
    if(P2IFG & BIT0)
    {
        add=1;
        led=0;
        P2IFG &= ~BIT0;
    }
    else if(P2IFG & BIT1)
    {
        add=-1;
        led=255;
        P2IFG &= ~BIT1;
    }
    __delay_cycles(2000);
}


