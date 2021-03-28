#include<msp430.h>
#define LED BIT7
void delay(unsigned int t)                  // Custom delay function
{
    unsigned int i;
    for(i = t; i > 0; i--)
        __delay_cycles(50);                 // __delay_cycles accepts only constants !
}
int main(void)
{
    WDTCTL =  WDTPW + WDTHOLD;
    P1DIR |= LED;
    unsigned int j;
    while(1)
    {
        j=0;
        while(j <= 255)
        {
            P1OUT |= LED;
            if(j!=0) delay(j);
            P1OUT &= ~LED;
            if((255-j)!=0) delay(255-j);
            j++;
        }
        j=255;
        while(j > 0)
        {
            P1OUT |= LED;
            if(j!=0) delay(j);
            P1OUT &= ~LED;
            if((255-j)!=0) delay(255-j);
            j--;
        }
    }
    return 0;
}
