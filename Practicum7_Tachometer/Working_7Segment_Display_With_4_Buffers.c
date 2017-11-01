/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 13-10-2017 01:39
 * License: GPLv3 - General Public License version 3
 */
#ifndef F_CPU // Setup the clock speed so we delay loops work correct.
    #define F_CPU 1000000UL // 1 MHz clock speed
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define DISPLAY_DATA_DIR DDRA
#define DISPLAY_OUTPUT_PORT PORTA

#define SEGMENT_DATA_DIR DDRC
#define SEGMENT_OUTPUT_PORT PORTC

#define CONTROL_DATA_DIR DDRD
#define CONTROL_INPUT_PIN PORTD

volatile uint8_t screenBuffer[4][7] = {
        { 0xBF, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
        { 0xBF, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
        { 0xDF, 0xBF, 0xFB, 0xF7, 0xEF, 0xFE, 0xFF },
        { 0xDF, 0xBF, 0xFB, 0xF7, 0xEF, 0xFE, 0xFF }
};

volatile uint8_t screenBufferIndex = 0;
volatile uint8_t segmentBufferIndex = 0;


uint8_t displayEncodedNumbers[10][7] = {
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
 * This service routine is for updating the values displayed on the displays.
 * It gets activated every 255 clock ticks, so for 1mHz = 255 uS
 * The Timer Interrupt flag register: T0V0 gets reset.
 */
ISR(TIMER0_OVF_vect){
    TCNT0 = 125;
    if( segmentBufferIndex == 6 ){ // Is this the last segment in the buffer.
        segmentBufferIndex = 0; // Start from the first index.
        if( screenBufferIndex < 3 ){
            screenBufferIndex++; // Go the the next screen buffer.
        }
        else{
            screenBufferIndex = 0;
        }
    }
    DISPLAY_OUTPUT_PORT = ~(1<<screenBufferIndex); // Enable current display
    SEGMENT_OUTPUT_PORT = screenBuffer[screenBufferIndex][segmentBufferIndex]; // Enable current segment
    //segmentBufferIndex++; // Increment segment index for next timer overflow.
    segmentBufferIndex++;
}

/**
 * This function updates the values in the screen buffer. It takes an number as argument and parses it into
 * individual digits. Then it fills the screen buffers for each digit with the corresponding encoded segment values.
 *
 * @param number An number to be displayed on the the 7 segment displays.
 */
void updateScreenBuffer( uint16_t number )
{
    screenBufferIndex = 0; // The starting position of the screen buffer to fill.
    while( number ){ // While there are digits left to process.
        uint8_t digit = number % 10; // Get the last digit.
        number /=10; // Throw away the last digit.
        for ( int i = 0; i<7; ++i ) { // Load 7 single segment values for an certain number into the screen buffer.
            screenBuffer[screenBufferIndex][i] = displayEncodedNumbers[digit][i];
        }
    }

    while( screenBufferIndex < 4 ){ // Fill remaining displays with 0xff so the segments turn off.
        for ( int i = 0; i<7; ++i ) { // Load 7 single segment values for an certain number into the screen buffer.
            screenBuffer[screenBufferIndex][i] = 0xff;
        }
        screenBufferIndex--;
    }
}

void initiateIO()
{
    DISPLAY_DATA_DIR = 0xFF; // Configure all display ports as outputs.
    DISPLAY_OUTPUT_PORT = 0xFF; // Pull up every segment so they turn off.
    SEGMENT_DATA_DIR = 0xFF; // Configure all segment ports as outputs.
    SEGMENT_OUTPUT_PORT = 0xFF; // Pull up every segment so they turn off.
    //CONTROL_DATA_DIR = ~(1<<0) | ~(1<<1) | ~(1<<2) | ~(1<<3); // Configure [0...3] user control ports as inputs.
    //CONTROL_INPUT_PIN = (1<<4) | (1<<5) | (1<<6) | (1<<7); // Enable pull up resistors on the user input ports.
}

void initiateRegisters()
{
    MCUCR = ( 1<<ISC00 );   // Enable interrupt reaction
    TCCR0 = (1 << CS01); // Set up timer 0 with prescaler 8, 0.125 tick = 1 us
    TCNT0 = 125; // Initialize timer 0 tick counter to 125, update every ms.
    // TIMSK Timer Interrupt mask, TOIE0 Timer Overflow Interrupt Enable 0
    TIMSK = ( 1<< TOIE0); // Enable interrupts on an overflow of the Timer 0 register.
    sei(); // Enable global interrupts.
}

int main()
{
    initiateIO();
    initiateRegisters();

    while(1)
    {
        _delay_ms(10);
        //updateScreenBuffer(1);
        //PORTA = 0xff;
        //updateScreenBuffer( 3 );
    }
}