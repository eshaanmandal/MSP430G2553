#include <msp430.h> 
#define SEG_A BIT1
#define SEG_B BIT2
#define SEG_C BIT3
#define SEG_D BIT4
#define SEG_E BIT5
#define SEG_F BIT6
#define SEG_G BIT7

#define D0 (SEG_B + SEG_C + SEG_D + SEG_E + SEG_F + SEG_G)
#define D1 (SEG_D + SEG_G)
#define D2 (SEG_C + SEG_D + SEG_A + SEG_E + SEG_F)
#define D3 (SEG_C + SEG_D + SEG_A + SEG_G + SEG_F)
#define D4 (SEG_B + SEG_A + SEG_D + SEG_G)
#define D5 (SEG_C + SEG_B + SEG_A + SEG_G + SEG_F)
#define D6 (SEG_C + SEG_B + SEG_A + SEG_G + SEG_F + SEG_E)
#define D7 (SEG_C + SEG_D + SEG_G)
#define D8 (SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F + SEG_G)
#define D9 (SEG_A + SEG_B + SEG_C + SEG_D + SEG_F + SEG_G)
#define DA (SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_G)
#define DB (SEG_A + SEG_B + SEG_E + SEG_F + SEG_G)
#define DC (SEG_B + SEG_C + SEG_E + SEG_F)
#define DD (SEG_A + SEG_D + SEG_E + SEG_F + SEG_G)
#define DE (SEG_A + SEG_B + SEG_C + SEG_E + SEG_F)
#define DF (SEG_A + SEG_B + SEG_C + SEG_E)

#define CLEAR ~(SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F + SEG_G)
#define OPS (SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F + SEG_G)
#define FW3 BIT3
#define BW4 BIT4
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    const unsigned int numbers[]={D0,D1,D2,D3,D4,D5,D6,D7,D8,D9,DA,DB,DC,DD,DE,DF};
    int i=0;
    P1DIR |= OPS;
    P1OUT &= CLEAR;
    P1OUT |= D0;
    P2REN |= (FW3 + BW4);
    P2OUT |= (FW3 + BW4);
    while(1)
    {
        if(!(P2IN & FW3))
        {
            __delay_cycles(20000);
            while(!(P2IN & FW3))
                ;
            __delay_cycles(20000);
            i--;
            if(i < 0)
                i=15;

            P1OUT = (P1OUT & CLEAR) + numbers[i];
        }
        if(!(P2IN & BW4))
        {
            __delay_cycles(20000);
            while(!(P2IN & BW4))
                ;
            __delay_cycles(20000);
            i++;
            if(i > 15)
                i=0;

            P1OUT = (P1OUT & CLEAR) + numbers[i];
        }
    }
	return 0;
}
