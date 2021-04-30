#include <msp430.h> 

#define GREEN BIT6
#define AIN BIT0
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min)*(out_max - out_min)/(in_max - in_min);
}
void register_settings_TIMERA0()
{
   P1DIR |= GREEN;
   P1SEL |= GREEN;

   TACCR0 = 255;
   TACCR1 = 0;
   TACCTL1 |= OUTMOD_7;
   TACTL |= TASSEL_2 + MC_1;
}

void register_settings_ADC10()
{
    ADC10CTL0 |= SREF_0 + ADC10SHT_3 + ADC10ON;
    ADC10CTL1 |= INCH_0;
    ADC10AE0 |= AIN;
}
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	register_settings_TIMERA0();
	register_settings_ADC10();
	while(1)
	{
	    ADC10CTL0 |= ADC10SC + ENC; // start the coversion
	    while(ADC10CTL1 & ADC10BUSY)
	        ;
	    TACCR1 = map(ADC10MEM,0, 1023, 0, 255);
	}
}
