/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 10-09-2017 15:35
 * Licence: GPLv3 - General Public Licence version 3
 */
#ifndef GCCAPPLICATION3_SEVENSEGMENTDISPLAY_H
#define GCCAPPLICATION3_SEVENSEGMENTDISPLAY_H

#ifndef F_CPU // Setup the clock speed so we delay loops work correct.
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

// Use these to activate an specific number prefixing mode on the displays.
#define SEG7_PREFIX_MODE_OFF 0 // Turn off displays that are not used to show data.
#define SEG7_PREFIX_MODE_ZERO 1 // Prefix with zero's (default)
#define SEG7_PREFIX_MODE_HEX 3 // Hexadecimal prefix 0x
#define SEG7_PREFIX_MODE_BIN 5 // Binary prefix 0b
#define SEG7_PREFIX_MODE_MINUS 6 // Pre append with negative prefix -
#define SEG7_PREFIX_MODE_NOT 7 // Pre append with  negation character ¬
#define SEG7_PREFIX_MODE_EQUALS 8 // Pre append with equals sign =

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

/** Set the number base for printing on the segment displays.
 * @param numberBase The base like: BASE_DECIMAL, BASE_HEXADECIMAL or BASE_OCTAL
 */
void setPrintNumberBaseMode( uint8_t numberBase );

/** Use this to define how you want to prefix your numbers printed on the 7 segment display.
 * @param numberPrefixing The prefix to use when printing like: SEG7_PREFIX_MODE_ZERO = 0018 with leading zeros or
 * SEG7_PREFIX_MODE_HEX = 0xFF with the 0x notation.
 */
void setPrintNumberPrefixMode( uint8_t prefixMode );

/** Write an number to the connected segmented displays.
 * @param numberToBeDisplayed
 */
void writeNumbersToSegmentDisplays( int numberToBeDisplayed );

/** Count up with an certain interval.
 * @param updateInterval The time it displays an value on the displays.
 */
void countUp( uint16_t updateInterval );

#endif //GCCAPPLICATION3_SEVENSEGMENTDISPLAY_H
