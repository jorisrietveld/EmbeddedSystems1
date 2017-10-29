/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 22-10-2017 22:10
 * License: GPLv3 - General Public License version 3
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#define DISPLAY_DATA_DIR DDRA
#define SEGMENT_DATA_DIR DDRC
#define CONTROL_DATA_DIR DDRD
#define DISPLAY_OUTPUT_PORT PORTA
#define SEGMENT_OUTPUT_PORT PORTC
#define CONTROL_INPUT_PIN PORTD

volatile uint8_t timer0Overflows = 0;
volatile uint8_t screenBuffer[4][7] = {
        { [0 ...(6)] = 0xff },
        { [0 ...(6)] = 0xff },
        { [0 ...(6)] = 0xff },
        { [0 ...(6)] = 0xff },
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

void initiateTimers(){
    TCCR0 = (1 << CS00); // Set up timer 0 without prescaler
    TCNT0 = 0; // Initialize timer 0 tick counter to 0
    // TIMSK Timer Interrupt mask, TOIE0 Timer Overflow Interrupt Enable 0
    TIMSK |= ( 1<< TOIE0); // Enable interrupts on an overflow of the Timer 0 register.

    sei(); // Enable global interrupts.
}

void initiateIO(){
    DISPLAY_DATA_DIR = 0xff; // Configure all display ports as outputs.
    SEGMENT_DATA_DIR = 0xff; // Configure all segment ports as outputs.
    CONTROL_DATA_DIR |= ~(1<<0) | ~(1<<1) | ~(1<<2) | ~(1<<3); // Configure [0...3] user control ports as inputs.
    CONTROL_INPUT_PIN = (1<<4) | (1<<5) | (1<<6) | (1<<7); // Enable pull up resistors on the user input ports.
}

/**
 * This service routine is for updating the values displayed on the displays.
 * It gets activated every 255 clock ticks, so for 1mHz = 255 uS
 * The Timer Interrupt flag register: T0V0 gets reset.
 */
ISR(TIMER0_OVF_vect){
    screenBufferIndex %= 4; // Limit the screen buffer index to the amount of displays.
    if( segmentBufferIndex = 7 ){ // Is this the last segment in de buffer.
        screenBufferIndex++; // Go the the next screen buffer.
        segmentBufferIndex = 0; // Start from the first index.
    }
    DISPLAY_OUTPUT_PORT = ~(1<<screenBufferIndex); // Enable current display
    SEGMENT_OUTPUT_PORT = screenBuffer[screenBufferIndex][segmentBufferIndex]; // Enable current segment
    segmentBufferIndex++; // Increment segment index for next timer overflow.
}

/**
 * This function updates the values in the screen buffer. It takes an number as argument and parses it into
 * individual digits. Then it fills the screen buffers for each digit with the coresponding encoded segment values.
 *
 * @param newNumber An number to be displayed on the the 7 segment displays.
 */
void updateScreenBuffer( uint16_t newNumber )
{
    screenBufferIndex = 0; // The starting position of the screen buffer to fill.
    while( number ){ // While there are digits left to process.
        uint8_t digit = number % 10; // Get the last digit.
        number /=10; // Throw away the last digit.
        // TODO test if this works: screenBuffer[screenBufferIndex] = characterEncodings[digit];
        for ( int i = 0; i<7; ++i ) { // Load 7 single segment values for an certain number into the screen buffer.
            screenBuffer[screenBufferIndex][i] = characterEncodings[digit][i];
        }
    }
    while( screenBufferIndex < 4 ){ // Fill remaining displays with 0xff so the segments turn off.
        for ( int i = 0; i<7; ++i ) { // Load 7 single segment values for an certain number into the screen buffer.
            screenBuffer[screenBufferIndex][i] = 0xff;
        }
        screenBufferIndex--;
    }
}

void main()
{
    initiateIO();
    initiateTimers();
    updateScreenBuffer( 20 );

    while(1);
}

/**
 * 1 mhz timer0
 * 1 000 000 - 3 921, 56 overflows
 * 125 000 - 400,196
 * 15 625 -  61,274
 * 3 906, 25 - 15, 318
 * 976, 5625 - 3,829
 */
/*
ISR( TIMER0_0VF_vect )
{
    timer0Overflows++;
}

void timer0Init()
{
    TCCR0 |= (1<< CS00);
    TCNT9 = 0;
}

void updateScreenBuffer( uint16_t number ){
    uint8_t lastIndex = 28; // Screen buffer current index tracker.
    while( number ){ // While there are digits left to process.
        uint8_t digit = number % 10; // Get the last digit.
        number /=10; // Throw away the last digit.
        for ( int i = 0; i<7; ++i ) { // Load 7 single segment values for an certain number into the screen buffer.
            screenBuffer[lastIndex--] = characterEncodings[digit][i];
        }
    }
    while( lastIndex >=0 ){ // Fill remaining displays with 0xff so the segments turn off.
        screenBuffer[lastIndex--] = 0xff;
    }
}
int main(void){

    while (1) 
    {
    }
}

*/