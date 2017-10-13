/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 13-10-2017 01:39
 * License: GPLv3 - General Public License version 3
 */

#include <avr/io.h>
#include <stdbool.h>
#ifndef F_CPU // Setup the clock speed so we delay loops work correct.
    #define F_CPU 16000000UL // 16 MHz clock speed
#endif
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
static void writeSegmentSequence( uint8_t segmentByte, uint8_t displayIndex )
{
    PORTC = ~( 1 << displayIndex ); // Set the correct display.
    uint8_t testByte = 0b1000000;

    while( testByte > 0 )
    {
        // The testBytes (bitwise AND operator) segmentByte sequence for the character A looks like:
        // Bit to check  Compare  Inverted Encoded character    Inverted number to write to display.
        // 1000 0000        &       ~1000 0010 ( 0111 1101 )    = 0000 0000 ~=  1111 1111
        // 0100 0000        &       ~1000 0010 ( 0111 1101 )    = 0100 0000 ~=  1011 1111
        // 0010 0000        &       ~1000 0010 ( 0111 1101 )    = 0010 0000 ~=  1101 1111
        // 0001 0000        &       ~1000 0010 ( 0111 1101 )    = 0001 0000 ~=  1110 1111
        // 0000 1000        &       ~1000 0010 ( 0111 1101 )    = 0000 1000 ~=  1111 0111
        // 0000 0100        &       ~1000 0010 ( 0111 1101 )    = 0000 0100 ~=  1111 1101
        // 0000 0010        &       ~1000 0010 ( 0111 1101 )    = 0000 0000 ~=  1111 1111
        // 0000 0001        &       ~1000 0010 ( 0111 1101 )    = 0000 0001 ~=  1111 1110

        // 0000 0001 ^ 1000 0010 = 1000 0010
        // 0000 0001 & 1000 0010 = 0000 0000
        // 0000 0001 | 1000 0010 = 1000 0011

        // ~1111 1110 ^ 1000 0010 = 0111 1101
        // ~1111 1110 & 1000 0010 = 1000 0010

        // ~1111 1110 | 1000 0010 = 1111 1110
        // ~0111 1111 | 1000 0010 = 1111 1111
        // ~1011 1111 | 1000 0010 = 1011 1111

        PORTA = ~testByte | segmentByte;
        //PORTA = ~(testByte & ~segmentByte); // (bit index to check) & ~(encoded character/number)
        testByte >>= 1; // Shift the test byte 1 place to the right.
        _delay_us( 50 );
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
        }
        else
        {
            writeSegmentSequence( SEG7_DISPLAY_CHAR_N_UPPER, 0 );
            writeSegmentSequence( SEG7_DISPLAY_CHAR_O_UPPER, 1 );
        }
    }
}

