#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void adcInit();
void adcSwitch(uint8_t channel);
uint8_t adcRead();

#endif