#include <avr/io.h>

#include <stdint.h>

#include "pwm.h"

void pwmInit()
{
	// Disable prescalers
	GTCCR = (1<<TSM) | (1<<PSRASY) | (1<<PSRSYNC);

	// Timer settings
	TCCR0A = (1<<COM0A1) | (1<<COM0B1) | (1<<WGM01) | (1<<WGM00); // Non-inverting mode, Fast PWM mode 3	
	TCCR0B = (1<<CS00); // Sart timer with prescaler of 1
	
	TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10); // Non-inverting mode, 8-bit fast pwm mode 5
	TCCR1B = (1<<WGM12) | (1<<CS10); // 8-bit fast pwm mode 5, Prescaler of 1
	
	TCCR2A = (1<<COM2A1) | (1<<COM2B1) | (1<<WGM21) | (1<<WGM20); // Non-inverting mode, Fast PWM mode 3
	TCCR2B = (1<<CS20); // Sart timer with prescaler of 1
	
	// Enable prescalers at the same time for perfect synchronous control
	GTCCR = (1<<PSRASY) | (1<<PSRSYNC);
}

void pwmSetPercentage(uint8_t fan, uint8_t percentage)
{
	volatile uint8_t *port;
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
		default:
			return;
	}
	
	uint8_t value = percentage * 255 / 100;
	*port = value;
}