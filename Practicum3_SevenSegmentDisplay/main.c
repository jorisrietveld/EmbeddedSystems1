/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 10-09-2017 06:32
 * Licence: GPLv3 - General Public Licence version 3
 */

#include "Helpers.h" // Imported for some basic setup and helpful macros.
#include "SegDisplay.h" // Imported to make use of an 7 segment display.

/**
 * The entry point of the program.
 */
int main( void )
{
	// Configure the data direction registers;
    DDRA = DDRC = 0xff; // Initiate ports A and C to be outputs  for the segment displays.
	DDRD = 0x00; // Initiate ports D to be inputs for the switches and buttons.
	PORTD = 0xff; // Enable pull-up resistors for the inputs.
	
	while(1){
		writeNumbersToSegmentDisplays(10);
		//setPrintNumberBaseMode( BASE_HEXADECIMAL );
		//countUp( 200 );
	}
}