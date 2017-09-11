/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 10-09-2017 15:35
 * Licence: GPLv3 - General Public Licence version 3
 */

#ifndef GCCAPPLICATION3_SEVENSEGMENTDISPLAY_H
#define GCCAPPLICATION3_SEVENSEGMENTDISPLAY_H

#include <avr/io.h>
#include <inttypes.h>
#include "delaySpaceTime.h"

#define NUMBER_9 0b10010000;
#define NUMBER_8 0b10000000;
#define NUMBER_7 0b10011011;
#define NUMBER_6 0b11000000;
#define NUMBER_5 0b11010000;
#define NUMBER_4 0b10111000;
#define NUMBER_3 0b10010001;
#define NUMBER_2 0b10000101;
#define NUMBER_1 0b10111011;
#define NUMBER_0 0b10000010;

extern void writeToDisplay( uint16_t numberToDisplay );

#endif //GCCAPPLICATION3_SEVENSEGMENTDISPLAY_H
