#include <stdint.h>

#include "adc.h"
#include "mcp3008.h"
#include "temp.h"

void tempRead(uint8_t *temp)
{
	for (uint8_t i = 0; i != 6; i++) {
		temp[i] = mcp3008ReadChannel(i);
	}
}