/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 10-09-2017 15:35
 * Licence: GPLv3 - General Public Licence version 3
 */

#ifndef GCCAPPLICATION3_SEVENSEGMENTDISPLAY_H
#define GCCAPPLICATION3_SEVENSEGMENTDISPLAY_H

#include <avr/io.h>
#include <inttypes.h>
#include <avr/pgmspace.h>
#include "delaySpaceTime.h"
#include "sevenSegmentDisplay.h"

/** Write an raw byte to the segment ports.
 * @param byte The byte that wil be written to the segment port.
 */
void rawSetSegments( uint8_t byte );

/** Set an bit pattern to any display that is currently turned on.
 * @param number The number to be displayed on the display{s}
 */
void setNumericSegmentValue( uint8_t numericValueIndex );

/** Clear all bit patterns that are currently being displayed on the display(s).
 */
void clearSegments();

/** Set an raw byte to the display port.
 * @param byte The byte that will be written to the display port.
 */
void rawSetDisplays( uint8_t byte );

/** Activate an specific seven segment display so it will be available to write data to it.
 * @param number The displays index on the connected ports.
 */
void setDisplay( int displayIndex );

/** Deactivate an seven segment so it will no longer display any data.
 * @param number The displays index on the connected ports.
 */
void unSetDisplay( int number );

/** Deactivates all seven segment displays.
 */
void clearDisplays();

/** Clears all data both the segment ports and the display ports.
 */
void clearSegmentDisplays();

/** Write raw bytes to the segment displays.
 * @param segmentByte The byte for for the segment port.
 * @param displayByte The byte for the display port.
 */
void rawWriteDisplay( uint8_t segmentByte, uint8_t displayByte );

/** Write an numeric value to an segment certain display.
 * @param segmentByte The byte for for the segment port.
 * @param displayByte The byte for the display port.
 */
void numericWriteDisplay( uint8_t numericIndex, uint8_t displayIndex );

/** Parse an numeric value to an array with single digits for multiple number bases.
 * @param number The input number to be displayed on the segment displays.
 * @param base The number system base.
 */
void numberToDigitArray( int number, uint8_t base );

/** Set the number base for printing on the segment displays.
 * @param numberBase The base like: BASE_DECIMAL, BASE_HEXADECIMAL or BASE_OCTAL
 */
void setSegDisplayPrintBaseMode( uint8_t numberBase );

/** Set the prefix mode for printing on the segment displays. Modes are defined in "./SegmentDisplayPatterns.h"
 * @param numberPrefixing The prefix to use when printing like: SEG7_PREFIX_MODE_ZERO = 0018 with leading zeros or
 * SEG7_PREFIX_MODE_HEX = 0xFF with the 0x notation.
 */
void setSegDisplayPrefixMode( uint8_t numberPrefixing );

/** Write an number to the connected segmented displays.
 * @param numberToBeDisplayed
 */
void writeNumbersToSegmentDisplays( int numberToBeDisplayed );

#endif //GCCAPPLICATION3_SEVENSEGMENTDISPLAY_H
