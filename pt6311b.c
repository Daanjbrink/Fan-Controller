#include <util/delay.h>

#include <stdint.h>

#include "pt6311b.h"
#include "spi.h"

static void pt6311bWrite(uint8_t command)
{
	spiSelect(PT6311B);
	spiTransfer(command);
	spiUnselect();
}

void pt311bWriteLed(uint8_t led)
{
	spiSelect(PT6311B);
	spiTransfer(COMMAND_TWO | TWO_WRITE_LED);
	spiTransfer(led);
	spiUnselect();
}

static void pt6311bWriteData(uint8_t address, uint8_t *data, uint8_t length)
{
	spiSelect(PT6311B);
	spiTransfer(COMMAND_THREE | address);
	spiWriteData(data, length);
	spiUnselect();
}

uint8_t pt6311bRead(uint8_t command)
{
	spiSelect(PT6311B);
	spiTransfer(command);
	_delay_us(2);
	DDRB &= ~(1<<MOSI); // Tri-state miso before receiving
	uint8_t retval = spiTransfer(0);
	DDRB |= (1<<MOSI); // Un-tri-state
	spiUnselect();

	return retval;
}

void pt6311bInit()
{
	uint8_t ff[48] = {0xFF};
	
	// Set screen settings
	pt6311bWrite(COMMAND_ONE);
	
	// Clear screen
	pt6311bWrite(COMMAND_TWO | TWO_WRITE_DISPLAY);
	pt6311bWriteData(0, (uint8_t *) &ff, 48);

	// Turn on screen
	pt6311bWrite(COMMAND_FOUR | FOUR_DISPLAY_ON);
}

void pt6311bUpdateDisplay(uint8_t *data, uint8_t length)
{
	pt6311bWrite(COMMAND_TWO | TWO_WRITE_DISPLAY);
	pt6311bWriteData(0, data, (length > 48 ? 48 : length));
}