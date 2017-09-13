/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 10-09-2017 06:32
 * Licence: GPLv3 - General Public Licence version 3
 */

#include "initiateIO.h"
#include "sevenSegmentDisplay.h"

#define SEG7_DISPLAY_DISPLAY_PORT PORTD // I/O config for the segment display.
#define SEG7_DISPLAY_SEGMENT_PORT PORTC // I/O config for the segment display.

/**
 * The entry point of the program.
 */
int main( void )
{
    initiateIO(); // Setup all the required I/O pins.
	
	while(1)
	{
        //writeNumbersToSegmentDisplays( 8765 ); // Writes an integer to the 7 segment displays using multiplexing.
		//writeNumbersToSegmentDisplays(numberToDisplay);

		countUp(100);
		//writeNumbersToSegmentDisplays(10);
		
	}
}