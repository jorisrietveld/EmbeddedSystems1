/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 22-10-2017 22:10
 * License: GPLv3 - General Public License version 3
 */
#include <avr/io.h>
#include <avr/interrupt.h>
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
    DISPLAY_DATA_DIR |= ( 1 << 0 );
    DISPLAY_OUTPUT_PORT = ( 1 << 0 );
    TCCR1B |= (1 << CS10);

    for(;;)
    {
        if(TCNT1 == 49999)
        {
            DISPLAY_OUTPUT_PORT ^= (1<<0);
        }
    }
}