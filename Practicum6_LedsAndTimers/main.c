/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 13-10-2017 01:39
 * License: GPLv3 - General Public License version 3
 */

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "SegDisplayEncoding.h"

 

/**
 * Define boolean types.
 */
unsigned int timerInterruptCount = 0;
bool displayValue = false;

/**
 * The interrupt service routine
 * @return
 */
ISR ( TIMER0_OVF_vect )
{
    TCNT0 = 6; // The interrupt counter offset.

    if ( ++timerInterruptCount == 25 )
    {
        displayValue = !displayValue;
		timerInterruptCount = 0;
    }
}

/**
 * Write encoded number to the display using multiplexing.
 *
 * @param segmentByte The encoded number.
 * @param displayIndex The display to print it on.
 */
static void writeSegmentSequence( uint8_t segmentByte, uint8_t displayIndex, uint8_t totalLength )
{
    PORTC = ~( 1 << displayIndex ); // Set the correct display.
    for ( int i = 0; i < 7; ++i ) // Loop though every bit in an the segment display number encodings.
    {
        if ( !( segmentByte & ( 1 << i ))) // If the bit is 0 at the n'th position of the byte.
        {
            PORTA = ~( 1 << i ); // Turn on the corresponding segment (remember that 0 means on)
        } else {
            PORTA = 0xff;
        }
        _delay_us( 20 );
    }
}

int main( void )
{
    DDRA = DDRC = 0xff; // Initiate ports A and C as output ports.

    TCCR0 = _BV( CS01 ) | _BV( CS00 );
    TCNT0 = 6;
    TIMSK = _BV( TOIE0 );

    sei();

    /* Replace with your application code */
    while ( 1 )
    {
        if( displayValue )
        {
            writeSegmentSequence( SEG7_DISPLAY_CHAR_F_UPPER, 0 );
            writeSegmentSequence( SEG7_DISPLAY_CHAR_F_UPPER, 1 );
            writeSegmentSequence( SEG7_DISPLAY_CHAR_O_UPPER, 2 );
			writeSegmentSequence( 0xff, 2 );
        }
        else
        {
            writeSegmentSequence( SEG7_DISPLAY_CHAR_N_UPPER, 0 );
            writeSegmentSequence( SEG7_DISPLAY_CHAR_O_UPPER, 1 );
        }
    }
}

