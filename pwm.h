#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>

void pwmInit();
void pwmSetPercentage(uint8_t fan, uint8_t percentage);

#endif