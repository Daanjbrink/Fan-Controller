#include <stdint.h>

#include "serial.h"
#include "wifi.h"

void wifiInit()
{
	serialInit();
}

void wifiCommunicate(uint8_t *temp, uint16_t *fanrpm, uint8_t *automatic)
{
	serialWriteData(temp, 6);
	serialWriteData((uint8_t *)fanrpm, sizeof(fanrpm)*2);
	
	*automatic = serialRead();
}