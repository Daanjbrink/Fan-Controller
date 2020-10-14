#include <stdint.h>

#include "control.h"
#include "fan.h"

#define sizeof_first_array(x) (sizeof(x)/sizeof(x[0]))

static uint8_t fan_enabled[6] = {1, 1, 1, 1, 1, 1};
static uint8_t temp_graph[4][2] = {{25, 10}, {30, 25}, {40, 50}, {50, 100}};

void controlFanTemp(uint8_t *temp)
{
	for (uint8_t fan = 0; fan != 6; fan++) {
		if (!fan_enabled[fan]) {			
			continue;
		}

		uint8_t percentage = 0;
		for (uint8_t j = 0; j != sizeof_first_array(temp_graph); j++) {
			if (temp[fan] >= temp_graph[j][0]) {
				percentage = temp_graph[j][1];
			} else {
				break;
			}
		}

		if (fanGetPercentage(fan) != percentage) {
			fanSetPercentage(fan, percentage);
		}
	}
}

void controlFanPot(uint8_t *potmeter)
{
	for (uint8_t fan = 0; fan != 6; fan++) {
		volatile uint8_t *port = fanRegister(fan);
		if (*port != potmeter[fan]) {
			*port = potmeter[fan];
		}
	}
}
