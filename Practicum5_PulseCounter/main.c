/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 15-09-2017 02:44
 * License: GPLv3 - General Public License version 3
 */
#ifndef F_CPU // Setup the clock speed so we delay loops work correct.
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

volatile static uint8_t counterMode = 0; //  The mode of the pulse counter
volatile static uint16_t countedPulses = 0; // The counter
volatile static uint16_t countUp = 1; // The counter mode 3 tracker.
static uint8_t numberBase = 10; // The base the use when counting.

// Encoded numbers for 7 segment display, where the indexes correspond to the value being displayed. numbers 1 to 16 (hexadecimal) 
static uint8_t encodedNumbers[16] = { 0x82, 0xbb, 0x85, 0x91, 0xB8, 0xd0, 0xc0, 0x9B, 0x80, 0x90 ,0x88,	0xe0, 0xc6, 0xa1, 0xc4, 0xcc, };

/**
 * This function gets executed when the external interrupt 0 is triggered. It will track the state of the leds
 * and update there values accordingly. The pattern used:
 */
ISR (INT0_vect)
{
    switch( counterMode )
    {
        case 4:
            countedPulses++; // Increase the pulse count by one.
            countedPulses %= 10000;
            break;
        case 5:
            countedPulses--;
            countedPulses %= 10000;
            break;
        case 6:
            //countUp ? countedPulses++ : countedPulses--;

            if( countedPulses == 100 || countedPulses == 0 )
            {
                countUp ^= countUp;
            }
            break;
        case 7:
			
            break;
		default:
			countedPulses = 0;
			break;
    }

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
 *
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
    if( !( PIND & ( 1 << 4 )) )
	{
		counterMode = 4;
	}
	else if( !( PIND & ( 1 << 5 )) )
	{
		counterMode = 5;
	}
	else if( !( PIND & ( 1 << 6 )) )
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
 * This is the main
 * @return
 */
int main(void)
{
    DDRA = DDRC = 0xff; // Initiate ports A and C as output ports.
	PORTA = PORTD = 0xff;
    DDRD |= ~(1<<4) | ~(1<<5) | ~(1<<6) | ~(1<<7); // Set ports D [4-7] to be inputs.
    PORTD = (1<<4) | (1<<5) | (1<<6) | (1<<7); // Enable pull up resistors.

    // Enable interrupt 0 in the general interrupt control register.
	GICR = 1 << INT0;
	// Set the interrupt sens control bits in the MCU control register to listen for an raising edge event.
	MCUCR = 1 << ISC01 | 1 << ISC00;
	// Set enable interrupt to the control register so interrupts are enabled globally.
	sei();
	
    while (1) 
    {
        getActiveSwitch();
		writeNumbToDisplay(countedPulses);
    }
}
