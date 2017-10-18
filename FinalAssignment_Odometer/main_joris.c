/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 13-10-2017 01:39
 * License: GPLv3 - General Public License version 3
 *//*

#ifndef F_CPU // Setup the clock speed so we delay loops work correct.
    #define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "SegDisplayEncoding.h"

#define DISPLAY_COUNT 4 // The amount of connected displays.
#define DISPLAY_SELECTOR PORTC // The output ports connected to power of the each display, every bit means power this display on.
#define SEGMENT_SELECTOR PORTA // The output ports connected to drain of the each segment, every bit means enable drains on this segment.

*/
/**
 * Type of content alignment on the displays.
 *//*

enum ScreenAlignment{
    LEFT, RIGHT
};

*/
/**
 * 7 segment display variables.
 *//*

static uint8_t screenBuffer[DISPLAY_COUNT] = { [0 ... (DISPLAY_COUNT-1)] = 0xff }; // The display buffer, initiated with 255's
enum ScreenAlignment currentScreenAlignment = RIGHT; // The current content alignment on the displays.
uint8_t bufferShifts = 0; // Shifted places in buffer alignment.

*/
/**
 * Interrupt counters and trackers.
 *//*

uint16_t timerInterruptCount = 0; // The interrupt counter.
uint16_t countedWheelPulses = 0; // This variable contains the amount of pulses that the odometer created.
uint16_t dayMeterStartValue = 0; // This variable gets set from the countedWheelPulses when the day meter reset button is pressed.

bool displayValue = false; // Display on or off;



void writeStringToDisplay( char inputString[] );
static void writeDisplaySequence( uint8_t *screenBuffer );
static void writeSegmentSequence( uint8_t segmentByte, uint8_t displayIndex );
static void flushBuffer();
static void writeBuffer();

*/
/**
 * This function gets executed when the external interrupt 0 is triggered. It will count incoming pulses.
 *//*

ISR (INT0_vect)
{
    countedPulses++; // Increase the pulse count by one.
}

*/
/**
 * The interrupt service routine
 * @return
 *//*

ISR ( TIMER0_OVF_vect )
{
    displayValue = !displayValue;
    timerInterruptCount = 0;
}

int main( void )
{
    DDRA = DDRC = 0xff; // Initiate ports A and C as output ports.
    DDRD |= ~(1<<4) | ~(1<<5) | ~(1<<6) | ~(1<<7); // Set ports D [4-7] to be inputs.
    PORTD = (1<<4) | (1<<5) | (1<<6) | (1<<7); // Enable pull up resistors.

    TCCR0 = ( 1 << CS10 );
    TCNT0 = 0;
    TIMSK = ( 1 << TOIE0 );

    // Enable interrupt 0 in the general interrupt control register.
    GICR = 1 << INT0;
    // Set the interrupt sens control bits in the MCU control register to listen for an raising edge event.
    MCUCR = ( 1 << ISC01 ) | ( 1 << ISC00 );
    // Set enable interrupt to the control register so interrupts are enabled globally.
    sei();

    */
/* Replace with your application code *//*

    while ( 1 ) {
        if( displayValue )
        {
            currentScreenAlignment = LEFT;
            screenBuffer[0] = SEG7_DISPLAY_CHAR_O_UPPER;
            screenBuffer[1] = SEG7_DISPLAY_CHAR_N_UPPER;
            screenBuffer[2] = 0xff;
            screenBuffer[3] = 0xff;
            writeBuffer();
        }
        else
        {
            currentScreenAlignment = RIGHT;
            screenBuffer[0] = SEG7_DISPLAY_CHAR_O_UPPER;
            screenBuffer[1] = SEG7_DISPLAY_CHAR_N_UPPER;
            screenBuffer[2] = 0xff;
            screenBuffer[3] = 0xff;
            writeBuffer();
        }
    }
}

*/
/**
 * Tries to map an string to 7 segment display encoded bytes and push it to the screen buffer.
 * @param inputString
 *//*

void writeStringToDisplay( char inputString[] )
{
    uint8_t stringLength = sizeof(inputString) / sizeof(inputString[0]); // Calculate the length of the string.
}

*/
/**
 * Rotate the screen buffer to the right.
 *//*

static void rotateBufferRight()
{
    uint8_t first = screenBuffer[ 0 ]; // Save the first cell of the buffer so it can be placed at the end of the buffer.
    for ( uint8_t i = 0; i < (DISPLAY_COUNT-1); i++ ){ // Iterate over every buffer element.
        screenBuffer[ i ] = screenBuffer[ i + 1 ]; // Shift element to the left.
    }
    screenBuffer[ DISPLAY_COUNT -1 ] = first; // Set the last element to the first one.
}

*/
/**
 * Rotate the screen buffer to the left.
 *//*

static void rotateBufferLeft()
{
    uint8_t last = screenBuffer[ DISPLAY_COUNT-1 ]; // Save the last cell of the buffer so it can be placed at the beginning of the buffer.
    for ( uint8_t i = (DISPLAY_COUNT-1); i > 0; i-- ){ // Iterate over every buffer element.
        screenBuffer[ i ] = screenBuffer[ i-1 ]; // Shift element to the right.
    }
    screenBuffer[ 0 ] = last;  // Set the first to the last one.
}

*/
/**
 * Align the content of the buffer to the right.
 *//*

static void alignBufferRight()
{
    for ( uint8_t i = (DISPLAY_COUNT-1); i >= 0; i-- ) {
        if( screenBuffer[i] == 0xff || screenBuffer[i] == 0 ){
            rotateBufferLeft(); // Rotate the empty cell to the right so the real content will get aligned to the left.
            i++; // Check this cell again.
        } else {
            return; // We found some content to display, stop pushing the content to the right.
        }
    }
}

*/
/**
 * Align the contents of the buffer to the left.
 *//*

static void alignBufferLeft()
{
    for ( uint8_t i = 0; i < DISPLAY_COUNT; i++ ) {
        if( screenBuffer[i] == 0xff || screenBuffer[i] == 0 ) { // Is this cell in the buffer empty?
            rotateBufferRight(); // Rotate the empty cell to the right so the real content will get aligned to the left.
            i--; // Check this cell again.
        } else {
            return; // We found some content to display, stop pushing the content to the left.
        }
    }
}

*/
/**
 * Writes the current display buffer to the connected displays.
 *//*

static void writeBuffer()
{
    switch( currentScreenAlignment ) // Correct the buffer alignment.
    {
        case LEFT:
            alignBufferLeft();
            break;
        case RIGHT:
            alignBufferRight();
            break;
    }

    for ( uint8_t i = 0; i < DISPLAY_COUNT; i++ ) { // Write the buffer to the displays.
        writeSegmentSequence( screenBuffer[ i ], i );
    }
}

*/
/**
 * Flushes the content of the buffer.
 *//*

static void flushBuffer()
{
    for ( uint8_t i = 0; i < DISPLAY_COUNT; i++ ) {
        writeSegmentSequence( 0xff, i );
    }
}

*/
/**
 * Write encoded character to the display using multiplexing.
 *
 * @param segmentByte The encoded number.
 * @param displayIndex The display to print it on.
 *//*

static void writeSegmentSequence( uint8_t segmentByte, uint8_t displayIndex )
{
    DISPLAY_SELECTOR = ~( 1 << ( 3 - displayIndex )); // Set the correct display.
    uint8_t testByte = 0b1000000;

    while ( testByte > 0 ) {
        */
/**
         * How the encoder works for the encode character capital O, this will split the encoded character in 8 parts
         * and show each part for a short time. After 8 iterations the full character is displayed in 400 micro seconds.
         * Bit index is: The n'th iteration.
         * Test bit is: A comparison value to check if the segment is on, (0 = segment led on)
         * Encoded char is: The pattern of the 8 segments connected to the controller ( 1 is segment off, 0 is segment on )
         *
         * Bit index | Test bit  | OR |  Encoded char |  1/8 of the full encoded segment.
         * ----------|-----------+----+---------------+------------------------------------
         *     1     | 0111 1111   |     1000 0010       = 1111 1111    - Its an 0 so turn off the dot in the bottom right corner.
         *     2     | 1011 1111   |     1000 0010       = 1011 1111    - Turn on segment right top
         *     3     | 1101 1111   |     1000 0010       = 1101 1111    - Turn on segment top
         *     4     | 1110 1111   |     1000 0010       = 1110 1111    - Turn on segment left bottom
         *     5     | 1111 0111   |     1000 0010       = 1111 0111    - Turn on segment bottom
         *     6     | 1111 1011   |     1000 0010       = 1111 1011    - Turn on segment right bottom
         *     7     | 1111 1101   |     1000 0010       = 1111 1111    - Its an O so turn off the horizontal segment in the middle.
         *     8     | 1111 1110   |     1000 0010       = 1111 1110    - Turn on segment left top.
         *//*

        SEGMENT_SELECTOR = ~testByte | segmentByte;
        testByte >>= 1; // Shift the test byte 1 place to the right.
        _delay_us( 50 );
    }
}

void createNewSegmentBuffer()
{
    // TODO get bit patterns to display
    // TODO update the segment buffer to contain all
}
*/
