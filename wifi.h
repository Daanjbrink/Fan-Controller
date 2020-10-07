#ifndef WIFI_H_
#define WIFI_H_

#include <stdint.h>

void wifiInit();
void wifiCommunicate(uint8_t *temp, uint16_t *fanrpm, uint8_t *automatic);

#endif