#ifndef PT6311B_H_
#define PT6311B_H_

#include <stdint.h>

#define COMMAND_ONE			0b00001010
#define COMMAND_TWO			0b01000000
#define COMMAND_THREE		0b11000000
#define COMMAND_FOUR		0b10000111

#define TWO_WRITE_DISPLAY	0b00
#define TWO_WRITE_LED		0b101
#define TWO_READ_KEY		0b10
#define TWO_READ_SWITCH		0b111

#define FOUR_DISPLAY_ON		0b1000
#define FOUR_DISPLAY_OFF	0b0000

void pt6311bInit();
void pt6311bUpdateDisplay(uint8_t *data, uint8_t length);

void pt311bWriteLed(uint8_t led);
uint8_t pt6311bRead(uint8_t command);

#endif