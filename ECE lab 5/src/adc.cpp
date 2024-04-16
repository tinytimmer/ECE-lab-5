#include "adc.h"
#include <avr/io.h>

//got this from lectures, lab, and other github accounts to make sure this was correct ( i hope this is correct this time)
void initializeADC(){

   //set voltage reference to 5V
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << REFS1);

   //set to right adjusted
	ADMUX &= ~(1 << ADLAR);

   //set as single-ended input using ADC0 as input
	ADMUX &= ~((1 << MUX0) | (1 << MUX1) | (1 << MUX2) | (1 << MUX3) | (1 << MUX4) | (1 << MUX5));

   //set Auto-trigger with free-running fode
	ADCSRB &= ~((1 << ADTS0) | (1 << ADTS1) | (1 << ADTS2));

   //enable ADC and auto-triggering
	ADCSRA |= ((1 << ADEN) | (1 << ADATE));

   //set ADC clock frequency using prescaler
   //setting PS to 128, => sampling rate = 9615 KHz
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);

   //disable ADC0 pin as digital input, pin A0 on board
	DIDR0 |= (1 << ADC0D);

   //start 1st conversion to start free running conversions
	ADCSRA |= (1 << ADSC);
}