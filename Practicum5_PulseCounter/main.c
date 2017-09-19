/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 15-09-2017 02:44
 * License: GPLv3 - General Public License version 3
 */
#ifndef F_CPU // Setup the clock speed so we delay loops work correct.
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <util/delay.h>
#include <avr/io.h>

volatile uint8_t counterMode = 0; // 
volatile uint8_t numberBase = 10; // The base the use when counting.

// Encoded numbers for 7 segment display, where the indexes correspond to the value being displayed. numbers 1 to 16 (hexadecimal) 
static uint8_t encodedNumbers[16] = { 0x82, 0xbb, 0x85, 0x91, 0x8b, 0xd0, 0xc0, 0x9B, 0x80, 0x90 ,0x88,	0xe0, 0xc6, 0xa1, 0xc4, 0xcc, };

static void writeSegmentSequence( uint8_t segmentByte, uint8_t displayIndex)
{
    PORTA = ~( 1 << displayIndex ); // Set the correct display.
    for ( int i = 0; i < 7; ++i ) // Loop though every bit in an the segment display number encodings.
    {
        if( !( segmentByte & ( 1 << i ) ) ) // If the bit is 0 at the n'th position of the byte.
        {
            PORTC = ~( 1 << i ); // Turn on the corresponding segment (remember that 0 means on)
        }
		_delay_us(20);     
    }
}

static void writeNumbToDisplay(uint16_t number)
{
	uint8_t index = 0; // Tracks the display that is being written on. 
	
	while( number ) // While there is something left of the number to display.
	{
		uint8_t numberIndex = number % numberBase; // 
		writeSegmentSequence( encodedNumbers[ numberIndex ], index );
		number /= numberBase;
		index++;
	}
}

int main(void)
{
    DDRA = DDRC = 0xff;
	uint8_t displayCounter =10;
	
    while (1) 
    {
		writeNumbToDisplay(1810);
       // _delay_ms(1000);
		//_delay_ms(1);
        //readSwitches();
    }
}
