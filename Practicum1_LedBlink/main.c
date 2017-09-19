/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 05-09-2017 20:21
 * Licence: GPLv3 - General Public Licence version 3
 */
#include <avr/io.h>
#include "delaySpaceTime.h"

/**
 * Initiate I/O and other default settings on the atmega32.
 */
void init()
{
	DDRC = 0xFF; // Set I/O pin C[0-7] as output.
}

/**
 * The main entry point of the program.
 */
int main (void)
{
	init(); // Init I/O port

	while (1)
	{
		PORTC = 0x00; // LED there be light. On ports C[0-7]
		delayMilliSeconds( 500 ); // Stop the fabric of space time for haf a second.
		PORTC = 0xFF; // FF*ck light its dark now. On ports C[0-7]
		delayMilliSeconds( 500 ); // Again completely stop the micro controller from doing anything.
	}
}