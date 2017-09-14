/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 14-09-2017 01:57
 * Licence: GPLv3 - General Public Licence version 3
 */
#include <util/delay.h> // Import macros for delaying the execution of an program.

#include "Helpers.h" // Implements the embedded helpers interface.

/**
 * Delays the execution of an program for an given amount of microseconds.
 * @param microSeconds The microseconds to wait.
 */
void delayMicroSeconds(uint32_t microSeconds )
{
    while( microSeconds-- ){
        _delay_us(1);
    }
}

/**
 * Delays the execution of an program for an given amount of milliseconds.
 * @param milliSeconds The milliseconds to wait.
 */
void delayMilliSeconds( uint32_t milliSeconds )
{
    while( milliSeconds-- ){
        _delay_ms(1);
    }
}

