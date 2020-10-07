#include <avr/io.h>

#include <stdint.h>

#include "fan.h"

void fanInit()
{
	// Disable prescalers
	GTCCR = (1<<TSM) | (1<<PSRASY) | (1<<PSRSYNC);

	// Timer settings
	TCCR0A = (1<<COM0A1) | (1<<COM0B1) | (1<<WGM00); // Non-inverting mode, Phase correct PWM mode 3
	TCCR0B = (1<<CS00); // Sart timer with prescaler of 1
	
	DDRD = (1<<PORTD6);

	TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10); // Non-inverting mode, 8-bit phase correct pwm mode 5
	TCCR1B = (1<<CS10); // Prescaler of 1

	TCCR2A = (1<<COM2A1) | (1<<COM2B1) | (1<<WGM20); // Non-inverting mode, Phase correct PWM mode 3
	TCCR2B = (1<<CS20); // Sart timer with prescaler of 1

	// Enable prescalers at the same time for perfect synchronous control
	GTCCR = (1<<PSRASY) | (1<<PSRSYNC);
}

volatile uint8_t *fanRegister(uint8_t fan)
{
	volatile uint8_t *port = 0;
	switch (fan) {
		case 0:
			port = &OCR0A;
			break;
		case 1:
			port = &OCR0B;
			break;
		case 2:
			port = &OCR1AL;
			break;
		case 3:
			port = &OCR1BL;
			break;
		case 4:
			port = &OCR2A;
			break;
		case 5:
			port = &OCR2B;
			break;
	}
	return port;
}

uint8_t fanGetPercentage(uint8_t fan)
{
	uint8_t value = *fanRegister(fan);
	return value * 100 / 255;
}

void fanSetPercentage(uint8_t fan, uint8_t percentage)
{
	uint8_t value = percentage * 255 / 100;
	*fanRegister(fan) = value;
}