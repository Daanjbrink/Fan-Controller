#include <avr/io.h>

#include <stdint.h>

#include "serial.h"

void serialInit()
{
	UBRR0H = (BAUDRATE>>8);
    UBRR0L = BAUDRATE;
    UCSR0B = (1<<RXEN0) | (1<<TXEN0); // Enable transmitter
}

void serialWrite(uint8_t data)
{
	while (!(UCSR0A & (1<<UDRE0))); // Wait until UART is ready
	UDR0 = data;
}

uint8_t serialRead()
{
	while (!(UCSR0A & (1<<RXC0))); // Wait until UART is ready
	return UDR0;
}

void serialWriteData(uint8_t *data, uint8_t length)
{
	while (length--)
		serialWrite(*data++);
}

void serialReadData(uint8_t *data, uint8_t length)
{
	while (length--)
		*data++ = serialRead();
}