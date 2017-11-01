/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 31-10-2017 19:50
 * License: GPLv3 - General Public License version 3
 */
#ifndef F_CPU // Setup the clock speed so we delay loops work correct.
#define F_CPU 1000000UL // 1 MHz clock speed
#endif
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define DISPLAY_DATA_DIR DDRA // Data Direction Register of to the display selector ports.
#define DISPLAY_PIN PINA // Input Register of to the display selector ports.
#define DISPLAY_PORT PORTA // Output Register of the display selector ports, used to multiplex the segment leds.

#define SEGMENT_DATA_DIR DDRC // Data Direction Register of to the segment selector ports.
#define SEGMENT_PIN PINC  // Input Register of to the segment selector ports.
#define SEGMENT_PORT PORTC // Output Register of the display selector ports, used to multiplex the segment leds.

#define INPUT_DATA_DIR DDRD // Data Direction Register of to the external input ports.
#define INPUT_PIN PIND  // Input Register of to the external input ports, used to interact with the user and read data from the sensors.
#define INPUT_PORT PORTD // Output Register of the external input ports, used to enable pull-up registers.

volatile uint16_t timerOverflowCount = 0; // Count Timer 1 overflows to measure distance between input signals.
volatile uint16_t lastPulseMicrosecondsCount = 0; // Amount of microseconds since last external interrupt.
volatile uint8_t lastPulseOverflowCount = 0; // Amount of overflows since last external interrupt.

uint16_t lastCalculationTime = 0; // Contains the last amount of timer 1 overflows on the calculation.

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

void initIoRegisters();
void initiateTimers();
void initInterrupts();
void updateScreenBuffer( uint16_t number );

int main(){
    initIoRegisters();
    initiateTimers();
    initInterrupts();

    while(1){
        updateScreenBuffer(10);
        //asm volatile ("nop"); // Do nothing , No Operation
        if( timerOverflowCount - lastCalculationTime > 7 ){ //  Overflow occurs at 15.259 Hz so 7 ~ 0.5 s
            lastCalculationTime = timerOverflowCount;

            uint16_t overflows = timerOverflowCount - lastPulseOverflowCount; // Get amount of overflows since last pulse.
            uint16_t microSeconds = TCNT1 - lastPulseMicrosecondsCount; // Get remaining microseconds since last pulse.
            uint32_t microSecondsBetweenPulse = (overflows*65535)+microSeconds; // Calculate amount of microseconds since last pulse.
            uint16_t revolutionsPerMinute = microSecondsBetweenPulse * 60000000; // Calculate revolutions per minute
        }
    }
}

ISR(TIMER0_OVF_vect){
    TCNT0 = 182;
    SEGMENT_PORT = 0xff;
    if( segmentBufferIndex == 6 ){ // Is this the last segment in the buffer.
        segmentBufferIndex = 0; // Start from the first index.
        if( screenBufferIndex < 3 ){
            screenBufferIndex++; // Go the the next screen buffer.
        }else{
            screenBufferIndex = 0;
        }
    }
    DISPLAY_PORT = ~(1<<screenBufferIndex); // Enable current display
    SEGMENT_PORT = screenBuffer[screenBufferIndex][segmentBufferIndex++]; // Enable current segment
}

ISR(TIMER1_OVF_vect){
    timerOverflowCount++;     // Increment overflow counter.
}

ISR(INT0_vect){
    lastPulseMicrosecondsCount = TCNT1; // Save current amount of microseconds.
    lastPulseOverflowCount = timerOverflowCount; // Save current amount of overflows.
}

void initIoRegisters(){
    DISPLAY_DATA_DIR = SEGMENT_DATA_DIR = 0xFF; // Initiate data output I/O registers.
    INPUT_DATA_DIR = 0x0F; // Initiate data input I/O registers.

    DISPLAY_PORT = 0xFF;
	SEGMENT_PORT = 0xFF; // Turn of all segment leds.
    INPUT_DATA_DIR = 0x0F; // Enable pull-up resistors on the external input ports.
}

void initiateTimers(){
    TCCR0 = 1 << CS01; // Initiate Timer 0 for multiplexing the segment displays.
    TCNT0 = 182; // Initiate counter register of Timer 0.
    TCCR1B = 1 << CS10; // Initiate Timer 1 for tracking time between external inputs.
    TCNT1 = 0; // Initiate counter register of Timer 0.
}

void initInterrupts(){
    MCUCR = ( 1<<ISC00 ); // Configure Interrupt mode to respond to falling edges.
    TIMSK = 1<< TOIE0 | 1 << TOIE1;// Enable overflow interrupt on Timer 0 and Timer 1
    GICR = 1 << INT0; // Enable external interrupts on port D3.

    sei(); // Enable
}

/**
 * This function updates the values in the screen buffer. It takes an number as argument and parses it into
 * individual digits. Then it fills the screen buffers for each digit with the corresponding encoded segment values.
 *
 * @param number An number to be displayed on the the 7 segment displays.
 */
void updateScreenBuffer( uint16_t number )
{
    screenBufferIndex = 0; // The buffer for the least significant digit.

    while( number ){ // While there are digits left to process.
        uint8_t digit = number % 10; // Get the least significant digit.
        number /=10; // Throw away the least significant digit and move the the next.
        for ( int i = 0; i<7; ++i ) { // Load 7 single segment values for the digit into the screen buffer.
            if( screenBuffer[screenBufferIndex][i] != displayEncodedNumbers[digit][i] ) {
               screenBuffer[screenBufferIndex][i] = displayEncodedNumbers[digit][i];
            }
        }
    }

    while( screenBufferIndex < 4 ){ // Fill remaining buffers with 0xff so the segments turn off.
        for ( int i = 0; i<7; ++i ) { // Load 7 segment segment off commands into buffer.
            if( screenBuffer[screenBufferIndex][i] != 0xFF ) {
                screenBuffer[screenBufferIndex][i]  = 0xFF;
            }
        }
        screenBufferIndex++;
    }
}


