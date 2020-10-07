#include <stdint.h>

#include "mcp3008.h"
#include "spi.h"

uint8_t mcp3008ReadChannel(uint8_t channel)
{
	// Buffer according to MCP3008 datasheet figure 6-1
	channel |= (1<<4); // Set 4th bit
	channel <<= 4; // Shift lower 4 bits to upper 4 bits
	
	uint8_t upperbits, lowerbits;
	spiSelect(ADC);		
	spiTransfer(1); // Transfer start bit
	upperbits = spiTransfer(channel); // Transfer SGLDIFF and channel bits and retrieve upper 2 bits of the result
	lowerbits = spiTransfer(0); // Dummy load
	spiUnselect();
	
	return upperbits | (lowerbits>>2); // Return 8 bit value
}