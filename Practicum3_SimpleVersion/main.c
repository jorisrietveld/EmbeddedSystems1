/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 21-09-2017 23:55
 * License: GPLv3 - General Public License version 3
 */

#ifndef F_CPU // Setup the clock speed so we delay loops work correct.
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

static uint8_t counterMode = 0; //  The mode of the pulse counter
static uint8_t numberBase = 10; // The base the use when counting.
static uint16_t numberToDisplay = 5678;
static uint64_t counter = 0;
static uint64_t previousCount = 0;
static uint64_t counterInterval = 5;


// Encoded numbers for 7 segment display, where the indexes correspond to the value being displayed. numbers 1 to 16 (hexadecimal) 
static uint8_t encodedNumbers[16] = { 0x82, 0xbb, 0x85, 0x91, 0b10111000, 0xd0, 0xc0, 0x9B, 0x80, 0x90 ,0x88,	0xe0, 0xc6, 0xa1, 0xc4, 0xcc, };

ISR (TIMER2_COMP_vect)
{
    //numberToDisplay++;
    counter++;
}

/**
 * Write an encoded segment byte to an certain display.
 *
 * @param  segmentByte The number encoded in an byte to display an number on the display.
 * @param  displayIndex The display to write to.
 */
static void writeSegmentSequence( uint8_t segmentByte, uint8_t displayIndex)
{
    PORTA = ~( 1 << displayIndex ); // Set the correct display.
    for ( int i = 0; i < 7; ++i ) // Loop though every bit in an the segment display number encodings.
    {
        if( !( segmentByte & ( 1 << i ) ) ) // If the bit is 0 at the n'th position of the byte.
        {
            PORTC = ~( 1 << i ); // Turn on the corresponding segment (remember that 0 means on)
			_delay_us(20);
        }
    }
}

/**
 * Write an number with an maximum of 4 digits to the 7 segment display. 
 *
 * @param  number The number to be displayed.
 */
static void writeNumbToDisplay(uint16_t number)
{
    uint8_t index = 0; // Tracks the display that is being written on.

    while( number ) // While there is something left of the number to display.
    {
        uint8_t numberIndex = number % numberBase; //  Get the lowest  digit like: 123, get  3 by dividing by the number base and getting the remainder.
        writeSegmentSequence( encodedNumbers[ numberIndex ], index ); // Write the digit to the screen by getting the encoded value.
        number /= numberBase; // Throw away the lowest digit and move on the the next.
        index++; // Increase the display index.
    }
}

/**
 * Test if an certain switch is active by testing pins D input bit.
 *
 * @param switchNumber The number of the D input port.
 * @return Is this switch activated?
 */
static uint8_t isSwitchActive( uint8_t switchNumber )
{
    return !( PIND & ( 1 << switchNumber ));
}

/**
 *
 */
static void readSwitches()
{
    if ( isSwitchActive( 0 ))
    {
        numberToDisplay += 1000;
        previousCount = counter;
	}
    else if ( isSwitchActive( 1 ))
    {
        numberToDisplay += 100;
        previousCount = counter;
    }
    else if ( isSwitchActive( 2 ))
    {
        numberToDisplay += 10;
        previousCount = counter;
    }
    else if ( isSwitchActive( 3 ))
    {
		numberToDisplay += 1;
        previousCount = counter;
    }
    else if ( isSwitchActive( 7 ))
    {
        numberToDisplay = 0;
        previousCount = counter;
    }
}

int main(void)
{
    DDRA = DDRC = 0xff; // Initiate ports A and C as output ports.
    DDRD = 0x00; // Initiate ports D as input ports.

    OCR2 = 62;
    TIMSK |= (1 << OCIE2);//Set interrupt Mask register to activate overflow interrupt enable.
    TCCR2 |= (1 << WGM21) | (1 << CS22) | (1 << CS21) | (1 << CS20); // Set timer/counter control register to 256/1024
    sei();

    while (1)
    {
        writeNumbToDisplay(numberToDisplay);
        if( counter - previousCount > counterInterval )
        {
            readSwitches();
        }
        numberToDisplay %= 10000;
    }
}
