#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>

void fanInit();
volatile uint8_t *fanRegister(uint8_t fan);
uint8_t fanGetPercentage(uint8_t fan);
void fanSetPercentage(uint8_t fan, uint8_t percentage);

#endif