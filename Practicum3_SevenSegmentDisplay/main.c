/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 10-09-2017 06:32
 * Licence: GPLv3 - General Public Licence version 3
 */
#include "Helpers.h" // Imported for some basic setup and helpful macros.
#include "SegDisplay.h" // Imported to make use of an 7 segment display.

#define SEG7_DISPLAY_DISPLAY_PORT PORTB // I/O config for the segment display.
#define SEG7_DISPLAY_SEGMENT_PORT PORTC // I/O config for the segment display.

/**
 * The entry point of the program.
 */
int main( void )
{
	// Configure the data direction registers;
    DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0x00;
	PORTD = 0xFF; // Enable pull-up resistors for the inputs.

	while(1){
		setPrintNumberBaseMode( BASE_HEXADECIMAL );
		countUp( 200 );
	}
}