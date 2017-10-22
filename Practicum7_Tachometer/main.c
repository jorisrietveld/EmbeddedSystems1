/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 13-10-2017 01:39
 * License: GPLv3 - General Public License version 3
 */
#ifndef F_CPU // Setup the clock speed so we delay loops work correct.
    #define F_CPU 1000000UL // 1 MHz clock speed
#endif

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "SegDisplayEncoding.h"

#define DISPLAY_OUTPUT PORTC // The output ports connected to power of the each display, every bit means power this display on.
#define SEGMENT_OUTPUT PORTA // The output ports connected to drain of the each segment, every bit means enable drains on this segment.

volatile uint16_t timerInterruptCount = 0; // The interrupt counter.
volatile uint16_t countedPulses = 0; // The amount of pulses counted.

uint8_t segmentsDisabled = 0xff;
uint8_t encodedNumbers[16] = { 0x82, 0xbb, 0x85, 0x91, 0xB8, 0xd0, 0xc0, 0x9B, 0x80, 0x90 ,0x88, 0xe0, 0xc6, 0xa1, 0xc4, 0xcc, };
uint8_t* screenBuffer[4] = { &encodedNumbers[1], &segmentsDisabled, &segmentsDisabled, &segmentsDisabled};// The display buffer, initiated with 255's
///uint8_t encodedNumbers[16] = { 0x82, 0xbb, 0x85, 0x91, 0xB8, 0xd0, 0xc0, 0x9B, 0x80, 0x90 ,0x88, 0xe0, 0xc6, 0xa1, 0xc4, 0xcc, };
uint8_t testByte = 0b10000000;

void setScreenBuffer( uint16_t number );
void flushScreenBuffer();
void outputScreenBuffer();

/**
 * This function gets executed when the external interrupt 0 is triggered. It will count incoming pulses.
 */
ISR (INT0_vect){
    SEGMENT_OUTPUT = 0x00;
    DISPLAY_OUTPUT = 0x00;
    //setScreenBuffer(countedPulses++);
}

int main( void )
{
    DISPLAY_OUTPUT = SEGMENT_OUTPUT = 0xFF; // Initiate ports A and B as outputs.
    DDRD = 0x00; // Initiate ports D as inputs.

    GICR = (1<<INT0); // Enable external interrupt 0 in the general interrupt control register.
    MCUCR = (1<<ISC00); // Configure external interrupt 0 to be triggered at any logic chance.
    sei(); // Enable all interrupt
    while ( 1 )
	{
        outputScreenBuffer();
	}
}

/**
 * Writes the current display buffer to the connected displays.
 */
void outputScreenBuffer(){
    for ( uint8_t i = 0; i < 4; i++ ) { // Write the buffer to the displays.
        DISPLAY_OUTPUT = ~(1<<i); // Turn on the correct display
        testByte = 0b1000000; // Reset the testByte
        while ( testByte > 0 ) { // Loop 7 times for each segment
            SEGMENT_OUTPUT = ~(testByte | ~( (uint8_t)screenBuffer[ i ]) ); // Write 1 segment of an encoded number to the display.
            testByte >>= 1; // Shift the test byte 1 place to the right.
            _delay_us( 50 ); // Wait 50 ticks so the screen is bright enough.
        }
    }
}
/**
 * Flushes the content of the buffer.
 */
void flushScreenBuffer(){
    for ( uint8_t i = 0; i < 4; i++ ) {
        screenBuffer[i] = &segmentsDisabled;
    }
}

void setScreenBufferNumber( uint16_t numberToDisplay )
{
    uint8_t bufferIndex = 0;
    for( int i =0; i<4; i++)
    {
        // Get the last digit of an number, use it to lookup the encoded value and pass the encoded value to the buffer.
        screenBuffer[ bufferIndex ] = numberToDisplay ? &encodedNumbers[ numberToDisplay%10 ] : &segmentsDisabled;
        numberToDisplay /= 10;
    }
}