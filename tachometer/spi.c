#include <stdint.h>

#include "spi.h"

void spiInit()
{
	DDRA = (1<<MISO); // Set MISO as output

	USICR = (1<<USIWM0) | (1<<USICS1); // SPI mode, CLK pin as clock source
}

inline uint8_t spiTransfer(uint8_t data)
{
	while (!(USISR & (1<<USIOIF))); // Wait until data is shifted in
	USIDR = data; // Load the data register with the byte
	USISR |= (1<<USIOIF); // Clear flag
	return USIBR; // Return incomming data
}