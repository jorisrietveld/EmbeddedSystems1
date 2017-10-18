/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 12-09-2017 03:01
 * License: GPLv3 - General Public License version 3
 */

#ifndef EMBEDDEDSYSTEMS1_SEGMENTDISPLAYPATTERNS_H
#define EMBEDDEDSYSTEMS1_SEGMENTDISPLAYPATTERNS_H

/***********************************************************************************[ Encoded of numeric characters ] */
#define SEG7_DISPLAY_NUMBER_0 0b10000010 // The segment display encoded  number 0
#define SEG7_DISPLAY_NUMBER_1 0b10111011 // The segment display encoded  number 1
#define SEG7_DISPLAY_NUMBER_2 0b10000101 //The segment display encoded  number 2
#define SEG7_DISPLAY_NUMBER_3 0b10010001 // The segment display encoded  number 3
#define SEG7_DISPLAY_NUMBER_4 0b10111000 // The segment display encoded  number 4
#define SEG7_DISPLAY_NUMBER_5 0b11010000 // The segment display encoded  number 5
#define SEG7_DISPLAY_NUMBER_6 0b11000000 // The segment display encoded  number 6
#define SEG7_DISPLAY_NUMBER_7 0b10011011 // The segment display encoded  number 7
#define SEG7_DISPLAY_NUMBER_8 0b10000000 // The segment display encoded  number 8
#define SEG7_DISPLAY_NUMBER_9 0b10010000 // The segment display encoded  number 9
#define SEG7_DISPLAY_NUMBER_10 0b10001000 // The segment display encoded number 10 - Represented as upper case a
#define SEG7_DISPLAY_NUMBER_11 0b11100000 // The segment display encoded number 11 - Represented as lower case b
#define SEG7_DISPLAY_NUMBER_12 0b11000110 // The segment display encoded number 12 - Represented as upper case c
#define SEG7_DISPLAY_NUMBER_13 0b10100001 // The segment display encoded number 13 - Represented as lower case d
#define SEG7_DISPLAY_NUMBER_14 0b11000100 // The segment display encoded number 14 - Represented as lower case E
#define SEG7_DISPLAY_NUMBER_15 0b11001100 // The segment display encoded number 15 - Represented as upper case F
#define SEG7_DISPLAY_NUMBER_16 0b11000010 // The segment display encoded number 16 - Represented as upper case G
#define SEG7_DISPLAY_NUMBER_17 0b11101000 // The segment display encoded number 17 - Represented as lower case H


/***********************************************************************************[ Encoded of lowercase characters ] */
#define SEG7_DISPLAY_CHAR_A_LOWER 0b10000001 // The segment display encoded lower case character A
#define SEG7_DISPLAY_CHAR_B_LOWER 0b11100000 // The segment display encoded lower case character B
#define SEG7_DISPLAY_CHAR_C_LOWER 0b11100101 // The segment display encoded lower case character C
#define SEG7_DISPLAY_CHAR_D_LOWER 0b10100001 // The segment display encoded lower case character D
// E lower does not exist
// F lower does not exist
// G lower does not exist
#define SEG7_DISPLAY_CHAR_H_LOWER_ALT 0b11001000 // The segment display encoded lower case character H with an roof
#define SEG7_DISPLAY_CHAR_H_LOWER 0b11101000 // The segment display encoded lower case character H
// i lower does not exist
// J lower does not exist
// K lower does not exist
#define SEG7_DISPLAY_CHAR_L_LOWER 0b11100111 // The bit pattern to show the character lower case L
// M lower does not exist
#define SEG7_DISPLAY_CHAR_N_LOWER 0b11101001 // The bit pattern to show the character lower case N
#define SEG7_DISPLAY_CHAR_O_LOWER 0b11100001 // The bit pattern to show the character lower case O
// P lower does not exist
// Q lower does not exist
// R  lower does not exist
// S  lower does not exist
// T  lower does not exist
#define SEG7_DISPLAY_CHAR_U_LOWER 0b11100011 // The bit pattern to show the character lower case U
// V  lower does not exist
// W  lower does not exist
// X  lower does not exist
// Y  lower does not exist
// Z  lower does not exist


/***********************************************************************************[ Encoded of uppercase characters ] */
#define SEG7_DISPLAY_CHAR_A_UPPER 0b10001000  // The segment display encoded upper case character A
#define SEG7_DISPLAY_CHAR_B_UPPER 0b10000000  // The segment display encoded upper case character B
#define SEG7_DISPLAY_CHAR_C_UPPER 0b11000110  // The segment display encoded upper case character C
#define SEG7_DISPLAY_CHAR_D_UPPER 0b10000010  // The segment display encoded upper case character D
#define SEG7_DISPLAY_CHAR_E_UPPER 0b11000100  // The segment display encoded upper case character E
#define SEG7_DISPLAY_CHAR_F_UPPER 0b11001100  // The segment display encoded upper case character F
#define SEG7_DISPLAY_CHAR_G_UPPER 0b11000010  // The segment display encoded upper case character G
#define SEG7_DISPLAY_CHAR_H_UPPER 0b10101000 // The segment display encoded upper case character H (MISSING)
// I missing
//#define SEG7_DISPLAY_CHAR_J_UPPER 0b11110011 // The segment display encoded upper case character J ( CONFLICT )
#define SEG7_DISPLAY_CHAR_J_UPPER 0b10100011 // The segment display encoded upper case character J ( CONFLICT )
// K upper does not exist.
#define SEG7_DISPLAY_CHAR_L_UPPER 0b11100110 // The bit pattern to show the character upper case L
// M upper does not exist.
#define SEG7_DISPLAY_CHAR_N_UPPER 0b10001010 // The bit pattern to show the character upper case N
//#define SEG7_DISPLAY_CHAR_U_UPPER 0b10001010 // The segment display encoded upper case character O
#define SEG7_DISPLAY_CHAR_O_UPPER 0b10000010 // The segment display encoded upper case character O
#define SEG7_DISPLAY_CHAR_P_UPPER 0b10001100 // The segment display encoded upper case character P
// Q upper does not exist.
// R
#define SEG7_DISPLAY_CHAR_S_UPPER 0b11010000 // The segment display encoded upper case character S
// T
#define SEG7_DISPLAY_CHAR_U_UPPER 0b10100010 // The segment display encoded upper case character U
#define SEG7_DISPLAY_CHAR_U_UPPER 0b10100010 // The segment display encoded upper case character V
// W
#define SEG7_DISPLAY_CHAR_X_UPPER 0b10001000 // The segment display encoded upper case character X
// Y missing
#define SEG7_DISPLAY_CHAR_Z_UPPER 0b11010000 // The segment display encoded upper case character Z

/***********************************************************************[ Encoded of uppercase characters upside down] */
#define SEG7_DISPLAY_CHAR_ROTATE_180_A_UPPER 0b10001000 // The segment display encoded upper case character A upside down.
#define SEG7_DISPLAY_CHAR_ROTATE_180_F_UPPER 0b10110001 // The segment display encoded upper case character F upside down.
#define SEG7_DISPLAY_CHAR_ROTATE_180_P_UPPER 0b10100001 // The segment display encoded upper case character P upside down.
#define SEG7_DISPLAY_CHAR_ROTATE_180_Y_UPPER 0b11001000 // The segment display encoded upper case character Y upside down.

#define SEG7_DISPLAY_BLOCK_BRACKET_LEFT 0b11000110 // The segment display encoded left side block bracket.

#endif //EMBEDDEDSYSTEMS1_SEGMENTDISPLAYPATTERNS_H
