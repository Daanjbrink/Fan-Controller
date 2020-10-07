#include <avr/interrupt.h>

#include <util/delay.h>

#include "comm.h"
#include "fan.h"
#include "spi.h"

int main()
{
	spiInit();
	fanInit();

	sei();

    while (1)
    {
		fanCalculateRPM();
		_delay_ms(300);
    }
}

