/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 06-09-2017 14:35
 * Licence: GPLv3 - General Public Licence version 3
 */
#include "your_late.h"

/**
 * Function to delay the micro controller an n amount of micro seconds.
 */
void delayMicroSeconds(uint32_t microSeconds )
{
	microSeconds /= 10;
	for (int i = 0; i < microSeconds; i++)
	{
		_delay_us(1);
	}
}

/**
 * Function to delay the micro controller an n amount of milliseconds.
 */
void delayMilliSeconds( uint32_t milliSeconds )
{
	milliSeconds /= 10;
	for( int i = 0; i < milliSeconds; i++)
	{
		_delay_ms(1);
	}
}