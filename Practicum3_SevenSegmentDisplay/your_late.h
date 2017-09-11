/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 06-09-2017 14:22
 * Licence: GPLv3 - General Public Licence version 3
 */

#ifndef YOUR_LATE_H_
#define YOUR_LATE_H_

#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>

/************************************************************************/
/* Function to delay the micro controller an n amount of microseconds   */
/************************************************************************/
extern void delayMicroSeconds(uint32_t microSeconds );

/************************************************************************/
/* Function to delay the micro controller an n amount of milliseconds   */
/************************************************************************/
extern void delayMilliSeconds( uint32_t milliSeconds );

#endif /* YOUR_LATE_H_ */