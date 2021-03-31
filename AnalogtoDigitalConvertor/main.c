#include <msp430.h> 

#define LED BIT6
#define AIN BIT0
long map(long,long,long,long,long);
void register_setting_TIMERA0();
void register_setting_ADC10();
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	register_setting_TIMERA0();
	register_setting_ADC10();
	
	while(1)
	{
	    ADC10CTL0 |= ADC10SC + ENC;
	    while(ADC10CTL1 & ADC10BUSY)
	        ;
	    TACCR1 = map(ADC10MEM,0,1023,0,255);
	}

}
 void register_setting_TIMERA0()
 {
     P1DIR |= LED;  //select the pin 1.6 as the output
     P1SEL |= LED; // changing from output to timer mode (gives timer output)

     TACCR0 = 255;
     TACCTL1 = OUTMOD_7;
     TACCR1 = 1;
     TACTL = MC_1 + TASSEL_2;
 }
 void register_setting_ADC10()
 {
    ADC10AE0  = AIN;  // for deciding which pin should accept the analog input
    ADC10CTL0 |= (SREF_0 + ADC10SHT_0 + ADC10ON + ADC10SR); // sets reference voltage as Vcc, Sample Hold time to 4 *ADC10CLK's and turns ON the ADC
    //also sets sampling rate to 50ksps
    ADC10CTL1 |= INCH_0; //Sets the pin 1.0 as the A0
 }
 long map(long x, long in_min, long in_max, long out_min, long out_max)
 {
    return (x-in_min)*(out_max - out_min) / (in_max - in_min) + out_min;
 }
