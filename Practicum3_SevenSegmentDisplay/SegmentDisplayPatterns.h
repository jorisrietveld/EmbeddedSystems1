/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 12-09-2017 03:01
 * Licence: GPLv3 - General Public Licence version 3
 */

#ifndef EMBEDDEDSYSTEMS1_SEGMENTDISPLAYPATTERNS_H
#define EMBEDDEDSYSTEMS1_SEGMENTDISPLAYPATTERNS_H

/**
 * Define an list with binary patterns for switching the individual segments on each
 * 7 segment display block. The values are inversed so an 0 means that the led segment
 * is switched on and 1 means off.
 */
#define SEG7_DISPLAY_NUMBER_0 0b10000010; // The bit pattern to show the number 0.
#define SEG7_DISPLAY_NUMBER_1 0b10111011; // The bit pattern to show the number 1.
#define SEG7_DISPLAY_NUMBER_2 0b10000101; // The bit pattern to show the number 2.
#define SEG7_DISPLAY_NUMBER_3 0b10010001; // The bit pattern to show the number 3.
#define SEG7_DISPLAY_NUMBER_4 0b10111000; // The bit pattern to show the number 4.
#define SEG7_DISPLAY_NUMBER_5 0b11010000; // The bit pattern to show the number 5.
#define SEG7_DISPLAY_NUMBER_6 0b11000000; // The bit pattern to show the number 6.
#define SEG7_DISPLAY_NUMBER_7 0b10011011; // The bit pattern to show the number 7.
#define SEG7_DISPLAY_NUMBER_8 0b10000000; // The bit pattern to show the number 8.
#define SEG7_DISPLAY_NUMBER_9 0b10010000; // The bit pattern to show the number 9.

/**
 * Define an list with binary patterns for switching the individual segments on each
 * 7 segment display block. The values are inversed so an 0 means that the led segment
 * is switched on and 1 means off.
 */
#define SEG7_DISPLAY_CHAR_a 0b10000010; // The bit pattern to show the number a.
#define SEG7_DISPLAY_CHAR_b 0b10111011; // The bit pattern to show the number b.
#define SEG7_DISPLAY_CHAR_c 0b10000101; // The bit pattern to show the number c.
#define SEG7_DISPLAY_CHAR_d 0b10010001; // The bit pattern to show the number d.
#define SEG7_DISPLAY_CHAR_E 0b10111000; // The bit pattern to show the number E.
#define SEG7_DISPLAY_CHAR_F 0b11010000; // The bit pattern to show the number F.
#define SEG7_DISPLAY_CHAR_A 0b10001000; // The bit pattern to show the character A.
#define SEG7_DISPLAY_CHAR_a 0b10100000; // The bit pattern to show the character a.
#define SEG7_DISPLAY_CHAR_b 0b11100000; // The bit pattern to show the character b.
#define SEG7_DISPLAY_CHAR_C 0b10110001; // The bit pattern to show the character C.
#define SEG7_DISPLAY_CHAR_c 0b00000000; // The bit pattern to show the character c.
#define SEG7_DISPLAY_CHAR_D 0b11000010; // The bit pattern to show the character D lowercase b otherwise it would look like an 0.
#define SEG7_DISPLAY_CHAR_E 0b10110000; // The bit pattern to show the character E.
#define SEG7_DISPLAY_CHAR_F 0b10111000; // The bit pattern to show the character F.
#define SEG7_DISPLAY_CHAR_G 0b10100001; // The bit pattern to show the character G.
#define SEG7_DISPLAY_CHAR_H 0b11001000; // The bit pattern to show the character H.
#define SEG7_DISPLAY_CHAR_I 0b1; // The bit pattern to show the character I.
#define SEG7_DISPLAY_CHAR_J 0b11000011; // The bit pattern to show the character J.
#define SEG7_DISPLAY_CHAR_L 0b1; // The bit pattern to show the character L.
#define SEG7_DISPLAY_CHAR_N 0b1; // The bit pattern to show the character N.
#define SEG7_DISPLAY_CHAR_O 0b1; // The bit pattern to show the character O lowercase o otherwise it would look like an 0.
#define SEG7_DISPLAY_CHAR_P 0b1; // The bit pattern to show the character P.
#define SEG7_DISPLAY_CHAR_R 0b1; // The bit pattern to show the character R.
#define SEG7_DISPLAY_CHAR_S 0b1; // The bit pattern to show the character S.
#define SEG7_DISPLAY_CHAR_U 0b1; // The bit pattern to show the character U lowercase u otherwise it would look like an V.
#define SEG7_DISPLAY_CHAR_V 0b1; // The bit pattern to show the character V.
#define SEG7_DISPLAY_CHAR_X 0b1; // The bit pattern to show the character X.
#define SEG7_DISPLAY_CHAR_Y 0b1; // The bit pattern to show the character Y.
#define SEG7_DISPLAY_CHAR_Z 0b1; // The bit pattern to show the character Z.

/**
 * Define the available prefixing modes for printing data to the segment display.
 *
 * You can set the prefixing mode by calling setSegDisplayPrefixMode( prefixingModeConstant );
 * defined in the ./sevenSegmentDisplay header.
 */
#define SEG7_PREFIX_MODE_OFF = 0;
#define SEG7_PREFIX_MODE_ZERO = 1;
#define SEG7_PREFIX_MODE_HEX_UPPER = 2;
#define SEG7_PREFIX_MODE_HEX = 3;
#define SEG7_PREFIX_MODE_BIN_UPPER = 4;
#define SEG7_PREFIX_MODE_BIN = 5;
#define SEG7_PREFIX_MODE_MINUS = 6;
#define SEG7_PREFIX_MODE_NOT = 7;
#define SEG7_PREFIX_MODE_EQUALS = 8;
#define SEG7_PREFIX_MODE_DOTS = 9;

/**
 * Define setting constants for configuring the text alignment on the segment displays.
 *
 * You can set the text alignment of the segment displays by calling the setSegDisplayAlignmentMode( textAlignConstant );
 * defined in the ./sevenSegmentDisplay header.
 */
#define SEG7_PRINT_ALIGN_LEFT 1;
#define SEG7_PRINT_ALIGN_RIGHT 2;
#define SEG7_PRINT_ALIGN_CENTER 3;

/**
 * Define aliases for commonly used base's from number systems.
 *
 * These constants can be used as argument in the following functions:
 * setSegDisplayPrintBaseMode( baseConstant );
 * void numberToDigitArray( baseConstant );
 * defined in the ./sevenSegmentDisplay header. If not set it will usually take decimal as default.
 */
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

#endif //EMBEDDEDSYSTEMS1_SEGMENTDISPLAYPATTERNS_H
