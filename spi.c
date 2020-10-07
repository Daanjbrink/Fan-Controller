#include <avr/io.h>

#include <util/delay.h>

#include "spi.h"

void spiInit()
{
	DDRB  = (1<<MOSI) | (1<<SCK); // Set all pins as output except MISO
	PORTB |= (1<<TACHO); // Set chip select pins high
	SPCR  = (1<<SPE) | (1<<DORD) | (1<<MSTR) | (1<<CPOL) | (1<<CPHA) | (1<<SPR0); // SPI enable, LSB first, Master mode, mode 1,1, 1 MHz clock
}

void spiSelect(uint8_t port)
{
	PORTB &= ~(1<<port); // Set only that pin low
	_delay_us(1);
}

void spiUnselect()
{
	PORTB |= (1<<TACHO);
}

inline uint8_t spiTransfer(uint8_t data)
{
	SPDR = data; // Load the data register with the byte
	while (!(SPSR & (1<<SPIF))); // Wait until data is shifted out
	return SPDR; // Return incomming data
}

void spiWriteData(uint8_t *data, uint8_t length)
{
	while (length--)
		spiTransfer(*data++);
}

void spiReadData(uint8_t *data, uint8_t length)
{
	while (length--)
		*data++ = spiTransfer(0);
}