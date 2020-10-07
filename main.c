#include <avr/io.h>

#include <util/delay.h>

#include <stdint.h>

#include "control.h"
#include "fan.h"
#include "potmeter.h"
#include "spi.h"
#include "tacho.h"
#include "temp.h"
#include "wifi.h"

int main()
{
	spiInit();
	fanInit();
	potmeterInit();
	wifiInit();

	uint8_t automatic = 0;
	uint8_t potmeter[6];
	uint8_t temp[6];
	uint16_t fanrpm[6];

	while (1)
    {
		potmeterRead(potmeter);
		tempRead(temp);
		tachoRead(fanrpm);
		
		wifiCommunicate(temp, fanrpm, &automatic);

		if (automatic) {
			controlFanTemp(temp);
		} else {
			controlFanPot(potmeter);
		}
    }
}