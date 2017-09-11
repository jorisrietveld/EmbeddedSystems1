/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 05-09-2017 20:21
 * Licence: GPLv3 - General Public Licence version 3
 */
#include <avr/io.h>

void init()
{
	DDRC |= ( 1 << PC7);
}
/**
 * The entry point of the program.
 */
int main (void)
{
	init();
	while (1)
	{

	}
	return 0;
}