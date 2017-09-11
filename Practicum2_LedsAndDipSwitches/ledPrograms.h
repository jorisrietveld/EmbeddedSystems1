//
// Created by FuckMicrosoft on 10-9-2017.
/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 09-09-2017 03:40
 * Licence: GPLv3 - General Public Licence version 3
 */
#ifndef GCCAPPLICATION3_LEDPROGRAMS_H
#define GCCAPPLICATION3_LEDPROGRAMS_H

#include <avr/io.h>
#include "delaySpaceTime.h"

/**
 * Blink all leds
 */
void ledBlink( uint8_t delay, uint16_t times );

/**
 * Slide single led  from the left to the right
 */
void ledScanLeft(uint8_t delay, uint8_t times );

/**
 * Slide single led  from the left to the right
 */
void ledScanRight(uint8_t delay, uint8_t times );

/**
 * Slide an single led from left to right and back.
 */
void ledScan( uint8_t delay, uint16_t times, uint8_t inverse );

/**
 * Slide in all leds from left to right and back.
 */
void ledSlide( uint8_t delay, uint8_t times );

/**
 * Slide in all leds from the right to left and continue sliding until all leds are off.
 */
void slideOut( uint8_t delay, uint8_t times );

/**
 * Slide in all leds from left to right, then clear and slide in form right to left.
 */
void slideScan( uint8_t delay, uint8_t times );

/**
 * Start with 2 leds in the middle of the array and slide them on both sides to the end of the array and back.
 * @param delay
 */
void ledExpand(uint8_t delay);

/**
 * Blink S-O-S morse code to the user.
 */
void blinkSOS();

#endif //GCCAPPLICATION3_LEDPROGRAMS_H
