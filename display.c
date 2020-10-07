#include <stdint.h>

#include "display.h"
#include "pt6311b.h"

void displayInit()
{
	pt6311bInit();
}

void displayUpdate()
{
	//pt6311bUpdateDisplay(display_buffer, sizeof(display_buffer));
}

void displayCompile(uint8_t encoders, uint8_t *temps, uint8_t *fanrpm)
{
}

uint8_t displayGetEncoders()
{
	uint8_t retval = 0;
	
	pt311bWriteLed(0); // Channels 1 and 4
	uint8_t encoder = pt6311bRead(COMMAND_TWO | TWO_READ_SWITCH);
	if ((encoder & 1) == 1) {
		retval |= (1);
		
	}
	if ((encoder & 2) == 2) {
		retval |= (4 << 4);
	}
	
	pt311bWriteLed(2); // Channels 2 and 5
	encoder = pt6311bRead(COMMAND_TWO | TWO_READ_SWITCH);
	if ((encoder & 1) == 1) {
		retval |= (2);
		
	}
	if ((encoder & 2) == 2) {
		retval |= (5 << 4);
	}

	pt311bWriteLed(4); // Channels 3 and 6
	encoder = pt6311bRead(COMMAND_TWO | TWO_READ_SWITCH);
	if ((encoder & 1) == 1) {
		retval |= (3);
		
	}
	if ((encoder & 2) == 2) {
		retval |= (6 << 4);
	}
	
	return retval;
}