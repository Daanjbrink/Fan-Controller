#ifndef SERIAL_H_
#define SERIAL_H_

#define BAUDRATE ((F_CPU / (9600UL * 16)) - 1)

void serialInit();

void serialWrite(uint8_t data);
uint8_t serialRead();

void serialWriteData(uint8_t *data, uint8_t length);
void serialReadData(uint8_t *data, uint8_t length);

#endif