#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

#include <stdint.h>

#define MISO PINA5

void spiInit();

uint8_t spiTransfer(uint8_t data);

#endif