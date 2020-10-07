#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/atomic.h>

#include <stdint.h>

#include "comm.h"
#include "fan.h"

static volatile uint16_t input_timings[6][2];

void fanInit()
{
	TCCR1B = (1<<CS12); // Set prescaler of 256

	PCMSK0 = (1<<PCINT7) | (1<<PCINT3) | (1<<PCINT2) | (1<<PCINT1) | (1<<PCINT0); // Mask pin interrupts
	PCMSK1 = (1<<PCINT9) | (1<<PCINT8);
	GIMSK = (1<<PCIE1) | (1<<PCIE0); // Enable pin change interrupt
}

void fanCalculateRPM()
{
	ATOMIC_BLOCK (ATOMIC_RESTORESTATE) {
		TCCR1B &= ~(1<<CS12); // Stop timer

		for (uint8_t fan = 0; fan != 6; fan++) {
			uint16_t timing1 = input_timings[fan][0];
			uint16_t timing2 = input_timings[fan][1];
			if (timing1 > 0 && timing2 > 0) {
				if (timing2 <= timing1) {
					timing2 = (65535 - timing1) + timing2; // Handle case where timing2 has overflown
					timing1 = 0;
				}
				uint16_t diff = (timing2 - timing1);
				float rps = (31250 / (float)diff) * 60;
				fan_rpm[fan] = (uint16_t)rps / 2;

				input_timings[fan][0] = 0;
				input_timings[fan][1] = 0;
			}
		}

		TCCR1B |= (1<<CS12); // Restart timer
	}
}

ISR(PCINT0_vect)
{
	static uint8_t fandone[4];

	uint8_t port = PINA;
	uint16_t time = TCNT1;

	TCCR1B &= ~(1<<CS12); // Stop timer

	if (port & PA7) {
		commSendRpm();
		TCCR1B |= (1<<CS12); // Restart timer
		return;
	}

	for (uint8_t fan = 0; fan != 4; fan++) {
		uint8_t bit = (1<<fan);
		if (port & bit) {
			if (!input_timings[fan][fandone[fan]]) {
				input_timings[fan][fandone[fan]] = time; // Select [fan, x] based on whether [fan, 0] is empty or not
				fandone[fan] = !fandone[fan];
			}
		}
	}

	TCCR1B |= (1<<CS12); // Restart timer
}

ISR(PCINT1_vect)
{
	static uint8_t fandone[2];

	uint8_t port = PINB;
	uint16_t time = TCNT1;

	TCCR1B &= ~(1<<CS12); // Stop timer

	port >>= 5;

	for (uint8_t fan = 0; fan != 2; fan++) {
		uint8_t bit = (1<<fan);
		if (port & bit) {
			input_timings[fan+4][fandone[fan]] = time; // Select [fan, x] based on whether [fan, 0] is empty or not
			fandone[fan] = !fandone[fan];
		}
	}

	TCCR1B |= (1<<CS12); // Restart timer
}