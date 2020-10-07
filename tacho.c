#include <stdint.h>

#include "spi.h"
#include "tacho.h"

void tachoRead(uint16_t *fanrpm)
{
	spiSelect(TACHO);
	spiTransfer(1);
	spiReadData((uint8_t *)fanrpm, sizeof(uint16_t) * 6);
	spiUnselect();
}