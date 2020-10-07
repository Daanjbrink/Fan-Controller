#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

#include "pt6311b.h"

void displayInit();
void displayUpdate();
void displayCompile(uint8_t encoders, uint8_t *temps, uint8_t *fanrpm);
uint8_t displayGetEncoders(); // Has nothing to do with video encoding. Encoders mean rotary encoders which are sent to the GPIO of the display chip

#endif