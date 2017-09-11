/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 05-09-2017 20:21
 * Licence: GPLv3 - General Public Licence version 3
 */
#include "initiateIO.h"
#include "switches.h"

/**
 * The entry point of the program.
 */
int main (void)
{
	initiateIO();
	readSwitches();
	return 0;
}