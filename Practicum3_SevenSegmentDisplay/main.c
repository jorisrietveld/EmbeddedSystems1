/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 10-09-2017 06:32
 * Licence: GPLv3 - General Public Licence version 3
 */

#include "initiateIO.h"
#include "sevenSegmentDisplay.h"

/**
 * The entry point of the program.
 */
int main( void )
{
    initiateIO();
	while(1)
	{
		writeToDisplay( 1000 ); // Writes an 4 digit integer to the 7 segment displays using multiplexing.
		/*
		for(int i=0;i<5;i++)
		{
			PORTD = ~( 1 << i);
			PORTC = sevenSegmentDisplayNumbers1[theNumberToDisplay[i]];
			_delay_us(100);
			PORTD = ~( 0 << i);
		}*/
	}
}