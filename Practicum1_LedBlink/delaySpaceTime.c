/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 06-09-2017 14:00
 * Licence: GPLv3 - General Public Licence version 3
 */
#ifndef F_CPU // Define the clock speed to get the correct clock ticks to delay.
	#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h> // This file defines some macro's and constants for using I/O ports on the atmega32
#include <util/delay.h> // This file defines some functions for pausing code execution.

#include "delaySpaceTime.h" // Implements this header.

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