/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 15-09-2017 02:44
 * License: GPLv3 - General Public License version 3
 */
#ifndef F_CPU // Setup the clock speed so we delay loops work correct.
#define F_CPU 1000000UL // 1 MHz clock speed
#endif

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t countedPulses = 0;

uint8_t characterEncodings[10][7] = {
		{ 0xDF, 0xBF, 0xFB, 0xF7, 0xEF, 0xFE, 0xFF },  // Sequence of encoded segments to create the number 0
		{ 0xBF, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },  // Sequence of encoded segments to create the number 1
		{ 0xDF, 0xBF, 0xFD, 0xEF, 0xF7, 0xFF, 0xFF },  // Sequence of encoded segments to create the number 2
		{ 0xDF, 0xBF, 0xFD, 0xFB, 0xF7, 0xFF, 0xFF },  // Sequence of encoded segments to create the number 3
		{ 0xFE, 0xFD, 0xBF, 0xFB, 0xFF, 0xFF, 0xFF },  // Sequence of encoded segments to create the number 4
		{ 0xDF, 0xFE, 0xFD, 0xFB, 0xF7, 0xFF, 0xFF },  // Sequence of encoded segments to create the number 5
		{ 0xDF, 0xFB, 0xF7, 0xEF, 0xFE, 0xFD, 0xFF },  // Sequence of encoded segments to create the number 6
		{ 0xDF, 0xBF, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF },  // Sequence of encoded segments to create the number 7
		{ 0xDF, 0xBF, 0xFB, 0xF7, 0xEF, 0xFE, 0xFD },  // Sequence of encoded segments to create the number 8
		{ 0xDF, 0xBF, 0xFB, 0xF7, 0xFE, 0xFD, 0xFF },  // Sequence of encoded segments to create the number 9
};


/**
 * This function gets executed when the external interrupt 0 is triggered. It will track the state of the leds
 * and update there values accordingly. The pattern used:
 */
ISR (INT0_vect)
{
    countedPulses++;
}

/**
 * Write encoded number to the display using multiplexing.
 *
 * @param segmentByte The encoded number.
 * @param displayIndex The display to print it on.
 */
static void writeSegmentSequence( uint8_t segmentByte, uint8_t displayIndex)
{
	PORTC = ~( 1 << displayIndex ); // Set the correct display.
	for ( int i = 0; i < 7; ++i ) // Loop though every bit in an the segment display number encodings.
	{
		if( !( segmentByte & ( 1 << i ) ) ) // If the bit is 0 at the n'th position of the byte.
		{
			PORTA = ~( 1 << i ); // Turn on the corresponding segment (remember that 0 means on)
		}
		else
		{
			PORTA = 0xff;
		}
		_delay_us(20);
	}
}

/**
 * Displays an number on the seven segment display.

 * @param number The number to be printed on the display.
 */
static void writeNumbToDisplay(uint16_t number)
{
	if( number == 0 )
	{
		writeSegmentSequence( 0b10000010, 0 ); // Write the digit to the screen by getting the encoded value.
		writeSegmentSequence( 0b11100110, 1 ); // Write the digit to the screen by getting the encoded value.
		writeSegmentSequence( 0b11000100, 2 ); // Write the digit to the screen by getting the encoded value.
		writeSegmentSequence( 0b10101000, 3 ); // Write the digit to the screen by getting the encoded value.
	}
	else
	{
		uint8_t index = 0; // Tracks the display that is being written on.
		
		while( number ) // While there is something left of the number to display.
		{
			uint8_t numberIndex = number % numberBase; //  Get the lowest  digit like: 123, get  3 by dividing by the number base and getting the remainder.
			writeSegmentSequence( encodedNumbers[ numberIndex ], index ); // Write the digit to the screen by getting the encoded value.
			number /= numberBase; // Throw away the lowest digit and move on the the next.
			index++; // Increase the display index.
		}
	}
}

/**
 * Test if an certain switch is active by testing pins D input bit.
 * @param switchNumber The number of the D input port.
 * @return Is this switch activated?
 */
void getActiveSwitch()
{
    if( !( PIND & ( 1 << 4 )) ) // Count interrupts up, reset at 9999.
	{
		counterMode = 4;
	}
	else if( !( PIND & ( 1 << 5 )) ) // Count interrupts down, reset at 0.
	{
		counterMode = 5;
	}
	else if( !( PIND & ( 1 << 6 )) ) // Count interrupts up and down between 100.
	{
		counterMode = 6;
	}
	else if( !( PIND & ( 1 << 7 )) )
	{
		counterMode = 7;
	}
	else
	{
		counterMode = 0;
	}
}

/**
 * This is the main entry point of the program.
 */
int main(void)
{
    DDRA = DDRC = 0xff; // Initiate ports A and C as output ports.
    DDRD |= ~(1<<4) | ~(1<<5) | ~(1<<6) | ~(1<<7); // Set ports D [4-7] to be inputs.
    PORTD = (1<<4) | (1<<5) | (1<<6) | (1<<7); // Enable pull up resistors.
	
	GICR = 1 << INT0; // Enable interrupt 0 in the general interrupt control register.
	MCUCR = 1 << ISC01 | 1 << ISC00; // Set the interrupt sens control bits in the MCU control register to listen for an raising edge event.
	sei(); // Set enable interrupt to the control register so interrupts are enabled globally.
	
    while (1) 
    {
        getActiveSwitch();
		writeNumbToDisplay(countedPulses);
    }
}
