#include <msp430.h> 
#include<inttypes.h>
#include<stdio.h>
#include<stdlib.h>

#define RED BIT7
#define AIN BIT0

void delay(uint8_t t)
{
    uint16_t i;
    for(i=t; i > 0; i--)
        __delay_cycles(100);
}

void register_settings_for_ADC10()
{
    ADC10AE0 |= AIN;                            // P1.0 ADC option select
    ADC10CTL1 = INCH_0;                         // ADC Channel -> 1 (P1.0)
    ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON;  // Ref -> Vcc, 64 CLK S&H , ADC - ON
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR |= RED;
	register_settings_for_ADC10();
	while(1){
	    ADC10CTL0 |= ADC10SC + ENC; // starts ADC coversion
	    while(ADC10BUSY & ADC10CTL1)
	        ;
	    uint16_t seed = (ADC10MEM & 0xFF);   // Lower 8-bits of ADC conversion result as seed
	    uint16_t lfsr = seed;
	    uint16_t count = 0;
	    while(count <= 65535){
	        uint8_t bit;
	        bit = ((lfsr >> 0) ^ (lfsr >> 1) ^ (lfsr >> 3) ^ (lfsr >> 12));     // Taking taps
	        lfsr = (lfsr >> 1) | (bit << 15);

	        P1OUT = (lfsr & 0x01)<<7;  ;
	        count = count + 1;
	        delay(150);
	    }
	}
	return 0;
}
