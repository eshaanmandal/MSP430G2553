#include <msp430.h> 
#include<inttypes.h>
#include<stdio.h>
#include<stdlib.h>

#define AIN BIT0

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
#define CLEAR (SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F + SEG_G)

void register_settings_for_ADC10()
{
    ADC10AE0 |= AIN;                            // P1.0 ADC option select
    ADC10CTL1 = INCH_0;                         // ADC Channel -> 1 (P1.0)
    ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON;  // Ref -> Vcc, 64 CLK S&H , ADC - ON
}
void delay(uint8_t t)
{
    uint16_t i;
    for(i=t; i > 0; i--)
        __delay_cycles(1000);
}
void ssd(int num){
    switch(num){
    case 0:P1OUT &= ~CLEAR; P1OUT |= D0; break;
    case 1:P1OUT &= ~CLEAR; P1OUT |= D1;break;
    case 2:P1OUT &= ~CLEAR; P1OUT |= D2;break;
    case 3:P1OUT &= ~CLEAR; P1OUT |= D3;break;
    case 4:P1OUT &= ~CLEAR; P1OUT |= D4;break;
    case 5:P1OUT &= ~CLEAR; P1OUT |= D5;break;
    case 6:P1OUT &= ~CLEAR; P1OUT |= D6;break;
    case 7:P1OUT &= ~CLEAR; P1OUT |= D7;break;
    case 8:P1OUT &= ~CLEAR; P1OUT |= D8;break;
    case 9:P1OUT &= ~CLEAR; P1OUT |= D9;break;
    }
}
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= 0xFF;
	P1OUT &= ~CLEAR;
	register_settings_for_ADC10();
	while(1){
	    ADC10CTL0 |= ADC10SC + ENC; // starts ADC coversion
	    while(ADC10BUSY & ADC10CTL1)
	        ;
	    uint16_t seed = ADC10MEM;
	    uint16_t lfsr = seed;
	    uint16_t count = 0;
	    while(count <= 65535){
	        uint16_t bit;
	        bit = ((lfsr >> 0) ^ (lfsr >> 1) ^ (lfsr >> 3) ^ (lfsr >> 12));
	        lfsr = (lfsr >> 1) | (bit << 15);
	        ssd(lfsr & 0xF);
	        count = count + 1;
	        delay(150);
	    }
	}
}
