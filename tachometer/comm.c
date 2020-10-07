#include <stdint.h>

#include "comm.h"
#include "fan.h"
#include "spi.h"

void commSendRpm()
{
	uint8_t data = spiTransfer(0);
	if (data) {
		for (uint8_t i = 0; i != sizeof(fan_rpm); i++) { // 6 entries of 2 bytes
			spiTransfer(*(fan_rpm+i));
		}
	}
}