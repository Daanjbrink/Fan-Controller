#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "adc.h"

void adcInit()
{
	ADMUX = (1<<REFS0) | (1<<ADLAR); // Set aVcc reference, left align
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // Enable ADC, set prescaler to 128
	
	DIDR0 = 0xFF; // All 1 except 7:6
	
	ADCSRA |= (1<<ADSC); // Init ADC by starting first conversion after enabling
}

void adcSwitch(uint8_t channel)
{
	ADMUX &= 0xF0; // Clear lower 4 bits
	ADMUX |= channel & 0x0F;
}

uint8_t adcRead()
{
	ADCSRA |= (1<<ADSC); // Start conversion
	while (ADCSRA & (1<<ADSC)); // Wait till conversion is done
	return ADCH; // Combine upper 8 bits with lower 2 bits and return the 10-bit value
}