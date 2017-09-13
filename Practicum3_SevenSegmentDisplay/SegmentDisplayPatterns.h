/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 12-09-2017 03:01
 * License: GPLv3 - General Public License version 3
 */

#ifndef EMBEDDEDSYSTEMS1_SEGMENTDISPLAYPATTERNS_H
#define EMBEDDEDSYSTEMS1_SEGMENTDISPLAYPATTERNS_H

/********************************************************************************************************************************************[ Start of  Numbers - To base 16 ] */
#define SEG7_DISPLAY_NUMBER_0 0b10000010 // The bit pattern to show the number 0.
#define SEG7_DISPLAY_NUMBER_1 0b10111011 // The bit pattern to show the number 1.
#define SEG7_DISPLAY_NUMBER_2 0b10000101 // The bit pattern to show the number 2.
#define SEG7_DISPLAY_NUMBER_3 0b10010001 // The bit pattern to show the number 3.
#define SEG7_DISPLAY_NUMBER_4 0b10111000 // The bit pattern to show the number 4.
#define SEG7_DISPLAY_NUMBER_5 0b11010000 // The bit pattern to show the number 5.
#define SEG7_DISPLAY_NUMBER_6 0b11000000 // The bit pattern to show the number 6.
#define SEG7_DISPLAY_NUMBER_7 0b10011011 // The bit pattern to show the number 7.
#define SEG7_DISPLAY_NUMBER_8 0b10000000 // The bit pattern to show the number 8.
#define SEG7_DISPLAY_NUMBER_9 0b10010000 // The bit pattern to show the number 9.
#define SEG7_DISPLAY_NUMBER_10 0b10000001 // The bit pattern to show the number 10 - Represented as lower case a
#define SEG7_DISPLAY_NUMBER_11 0b11100000 // The bit pattern to show the number 11 - Represented as lower case  b
#define SEG7_DISPLAY_NUMBER_12 0b11100101 // The bit pattern to show the number 12 - Represented as lower case  c
#define SEG7_DISPLAY_NUMBER_13 0b10100001 // The bit pattern to show the number 13  - Represented as lower case  d
#define SEG7_DISPLAY_NUMBER_14 0b11000100 // The bit pattern to show the number 14 - Represented as upper case  E
#define SEG7_DISPLAY_NUMBER_15 0b11001100 // The bit pattern to show the number 13 - Represented as upper case F


/********************************************************************************************************************************************[ Start of  Characters Lower Case ] */
#define SEG7_DISPLAY_CHAR_A_LOWER 0b10000001 // The bit pattern to show the character lower case A
#define SEG7_DISPLAY_CHAR_B_LOWER 0b11100000 // The bit pattern to show the character lower case B
#define SEG7_DISPLAY_CHAR_C_LOWER 0b11100101 // The bit pattern to show the character lower case C 
#define SEG7_DISPLAY_CHAR_D_LOWER 0b10100001 // The bit pattern to show the character lower case D
// E lower does not exist
// F lower does not exist
// G lower does not exist
#define SEG7_DISPLAY_CHAR_H_LOWER_ALT 0b11001000 // The bit pattern to show the character lower case H with an roof
#define SEG7_DISPLAY_CHAR_H_LOWER 0b11101000 // The bit pattern to show the character lower case H
// i lower does not exist
#define SEG7_DISPLAY_CHAR_J_LOWER 0b11110011 // The bit pattern to show the character lower case J
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
/********************************************************************************************************************************************[ End of  Characters Lower Case ] */

#define SEG7_DISPLAY_CHAR_A_UPPER 0b10001000 // The bit pattern to show the character upper case A
// B lower does not exist
#define SEG7_DISPLAY_CHAR_C_UPPER 0b11000110 // The bit pattern to show the character upper case C
// D lower does not exist
#define SEG7_DISPLAY_CHAR_E_UPPER 0b11000100 // The bit pattern to show the character upper case E -
#define SEG7_DISPLAY_CHAR_F_UPPER 0b11001100 // The bit pattern to show the character upper case F
#define SEG7_DISPLAY_CHAR_G_UPPER 0b11000010 // The bit pattern to show the character upper case G


#define SEG7_DISPLAY_CHAR_O_UPPER 0b10000010 // The bit pattern to show the character upper case 0
#define SEG7_DISPLAY_CHAR_P_UPPER 0b10001100 // The bit pattern to show the character upper case P
#define SEG7_DISPLAY_CHAR_J_UPPER 0b10100011 // The bit pattern to show the character upper case J
#define SEG7_DISPLAY_CHAR_S_UPPER 0b11010000 // The bit pattern to show the character upper case S
#define SEG7_DISPLAY_CHAR_L_UPPER 0b11100110 // The bit pattern to show the character upper case L
#define SEG7_DISPLAY_CHAR_U_UPPER 0b10100010 // The bit pattern to show the character upper case U

#define SEG7_DISPLAY_CHAR_X_UPPER 0b10001000 // The bit pattern to show the character upper case A

#define SEG7_DISPLAY_CHAR_ROTATE_180_A_UPPER 0b10001000 // The bit pattern to show the character upper case A
#define SEG7_DISPLAY_CHAR_ROTATE_180_P_UPPER 0b10100001

#define SEG7_DISPLAY_CHAR_ROTATE_180_Y 0b11001000 // The bit pattern to show the character y upside down 
#define SEG7_DISPLAY_CHAR_ROTATE_180_F 0b10110001 // The bit pattern to show the character F upside down 

#define SEG7_DISPLAY_BLOCK_BRACKET_LEFT 0b11000110 // The bit pattern to show the character G. checked [ V ]



#endif //EMBEDDEDSYSTEMS1_SEGMENTDISPLAYPATTERNS_H
