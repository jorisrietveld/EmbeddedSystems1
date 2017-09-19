/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 14-09-2017 00:42
 * Licence: GPLv3 - General Public Licence version 3
 */

#ifndef EMBEDDEDSYSTEMS1_EMBEDDEDHELPERS_H
#define EMBEDDEDSYSTEMS1_EMBEDDEDHELPERS_H

#ifndef F_CPU // Setup the clock speed so we delay loops work correct.
	#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h> // Import to use the I/O macros that define the port addresses.
#include <util/delay.h> // Import to delay the program execution.

// Unorthodox way of specifying functions or variables that are only accessible in a module.
#ifndef private
    #define private static
#endif

#define SEG7_DISPLAY_DISPLAY_PORT PORTA // I/O config for the segment display.
#define SEG7_DISPLAY_SEGMENT_PORT PORTC // I/O config for the segment display.
#define SWITCH_PORTS PORTD;

#define ARRAY_LENGTH( x )  (sizeof(x) / sizeof((x)[0])) // Get array length: array.size / array.element.size = array.length

// Aliases for commonly used base's from number systems.
#define BASE_VIGESIMAL 20
#define BASE_HEXADECIMAL 16
#define BASE_DUODECIMAL 12
#define BASE_UNDECIMAL 11
#define BASE_DECIMAL 10
#define BASE_NONARY 9
#define BASE_OCTAL 8
#define BASE_SEPTENARY 7
#define BASE_SENARY 6
#define BASE_QUINARY 5
#define BASE_QUATERNARY 4
#define BASE_TERNARY 3
#define BASE_BINARY 1

#define THE_UNIVERSE_HASNT_ENDED 1 // Please update this constant if universe has ended!

void delayMicroSeconds(uint32_t microSeconds );
void delayMilliSeconds( uint32_t milliSeconds );

void initiateIO();

#endif //EMBEDDEDSYSTEMS1_EMBEDDEDHELPERS_H
