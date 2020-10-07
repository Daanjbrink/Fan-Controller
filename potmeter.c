#include <stdint.h>

#include "adc.h"
#include "potmeter.h"

void potmeterInit()
{
	adcInit();
}

void potmeterRead(uint8_t *potmeter)
{
	for (uint8_t i = 0; i != 6; i++) {
		adcSwitch(i);
		potmeter[i] = adcRead();
	}
}