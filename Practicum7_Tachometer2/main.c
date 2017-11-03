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

//#define TIMER0_DISPLAY_REFRESH // Handle the multiplexing by timer 1.

#define DISPLAY_DATA_DIR DDRA // Data Direction Register of to the display selector ports.
#define DISPLAY_PIN PINA // Input Register of to the display selector ports.
#define DISPLAY_PORT PORTA // Output Register of the display selector ports, used to multiplex the segment leds.

#define SEGMENT_DATA_DIR DDRC // Data Direction Register of to the segment selector ports.
#define SEGMENT_PIN PINC  // Input Register of to the segment selector ports.
#define SEGMENT_PORT PORTC // Output Register of the display selector ports, used to multiplex the segment leds.

#define INPUT_DATA_DIR DDRD // Data Direction Register of to the external input ports.
#define INPUT_PIN PIND  // Input Register of to the external input ports, used to interact with the user and read data from the sensors.
#define INPUT_PORT PORTD // Output Register of the external input ports, used to enable pull-up registers.

volatile uint64_t timerOverflowCount = 0; // Count Timer 1 overflows to measure distance between input signals.
volatile uint64_t lastPulseMicrosecondsCount = 0; // Amount of microseconds since last external interrupt.
volatile uint64_t overflowBetweenPusesCount = 0;
volatile uint64_t lastPulseOverflowCount = 0; // Amount of overflows since last external interrupt.
uint16_t lastCalculationTime = 0; // Contains the last amount of timer 1 overflows on the calculation.

volatile uint16_t countedPulses = 0;
volatile uint16_t rpm = 0;

// The encoded segment bytes, number 11 is an hack to turn off displays.
volatile uint8_t encodedNumbers[11] = { 0x82, 0xBB, 0x85, 0x91, 0xB8, 0xD0, 0xC0, 0x9B, 0x80, 0x90, 0xFF };
volatile uint8_t screenOutputBuffer[4] = { 0, 1, 10, 10 }; // The numbers currently being multiplexed on the displays.
volatile uint8_t displayIndex = 0; // The current display that is turned on during multiplexing.
volatile uint8_t testByte = 0b1000000; // An byte to break every encoded segment into 7 single segment pieces.

void initIoRegisters();
void initiateTimers();

void writeScreenBuffer( uint16_t number ); // Define function to display an number to the screens.
void outputScreenBuffer(); // Define function to write the the displays.

/**
 * The main program routine.
 * @return null.
 */
int main(){
    initIoRegisters(); // Initiate the I/O registers.
    initiateTimers(); // Initiate the timer registers.
    while(1){
        outputScreenBuffer(); // Output the buffer.
        writeScreenBuffer( rpm );
    }
}

ISR(TIMER0_OVF_vect){

}

ISR(TIMER1_OVF_vect){
    timerOverflowCount++; // Increment overflow counter.
    rpm = countedPulses / 1.025; //Bereken de toeren per minuut,
    countedPulses = 0; //Zet het aantal getelde pulsen weer op 0.
}

ISR(INT0_vect){
    countedPulses++;
}

void initIoRegisters(){
    DISPLAY_DATA_DIR = 0xFF;
    SEGMENT_DATA_DIR = 0xFF; // Initiate data output I/O registers.
    INPUT_DATA_DIR = (1<<0) | (1<<1) | (1<<2) | (1<<3); // Initiate data input I/O registers.
    DISPLAY_PORT = 0xFF; // Turn of all display selectors.
    SEGMENT_PORT = 0xFF; // Turn of all segment leds.
    INPUT_PORT = 0x00; // Enable pull-up resistors on the external input ports.
}

void initiateTimers(){
    TCCR0 = 1 << CS01; // Initiate Timer 0 for multiplexing the segment displays.
    TCNT0 = 182; // Initiate counter register of Timer 0.
    TCCR1B = 1 << CS10; // Initiate Timer 1 for tracking time between external inputs.
    TCNT1 = 0; // Initiate counter register of Timer 0.
}

void outputScreenBuffer()
{
    if( testByte == 0b0000000 ){ // If an complete segment is written to the screen.
        testByte = 0b1000000;     // reset testByte

        if( displayIndex < 3 ){ // If there are more displays.
            displayIndex++; // Increment display index
        }else {
            displayIndex = 0; // Reset displays and start over.
        }
    }
    SEGMENT_PORT = 0xFF; // Make sure all segments are off, to prevent shadows of numbers.
    DISPLAY_PORT = ~( 1 << displayIndex ); // Enable the correct display port.
    // get an single segment from an encoded segment byte and display it on the screen.
    SEGMENT_PORT = ~testByte | encodedNumbers[ screenOutputBuffer[ displayIndex] ];
    testByte >>= 1; // Shift to the next segment.
}

void writeScreenBuffer( uint16_t number ){ // 123
    uint8_t i;
    volatile uint8_t digit;

    for( i = 0; i < 4; i ++){ // For each screen buffer index.
        if( number > 0 ){ // Are there digits to inject into the screen buffer.
            digit = number % 10; // Optimized away???? I need that !
            number = number / 10; // Go to the next digit.
        }
        else { // There are no new digits to insert into the buffer.
            //digit = 10; // 11 is the encoded character for turning off displays.
        }
        if( screenOutputBuffer[1] != digit ){
            screenOutputBuffer[i] = digit; // Get the least significant digit of the number and write it to the buffer.
        }
    }
}

