/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 31-10-2017 15:31
 * License: GPLv3 - General Public License version 3
 */
#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define DISPLAY_DATA_DIR DDRA
#define SEGMENT_DATA_DIR DDRC
#define CONTROL_DATA_DIR DDRD
#define DISPLAY_OUTPUT_PORT PORTA
#define SEGMENT_OUTPUT_PORT PORTC
#define CONTROL_INPUT_PIN PORTD

// global variable to count the number of overflows
volatile uint8_t tot_overflow;

int main()
{
    DISPLAY_DATA_DIR |= 0xff;
    DISPLAY_OUTPUT_PORT = 0xff;
    TCCR1B |= (1 << CS10);
	
	while(1)
	{

		_delay_ms(500);
		DISPLAY_OUTPUT_PORT ^= ( 1 << 7 );
	}
	
/*
    for(;;)
    {
        if(TCNT1 >= 49999)
        {
            DISPLAY_OUTPUT_PORT ^= (1<<0);
        }
    }*/
}
