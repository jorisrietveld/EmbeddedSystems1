/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 03-11-2017 10:24
 * License: GPLv3 - General Public License version 3
 */
#define DISPLAY_DATA_DIR DDRA // Data Direction Register of to the display selector ports.
#define DISPLAY_PIN PINA // Input Register of to the display selector ports.
#define DISPLAY_PORT PORTA // Output Register of the display selector ports, used to multiplex the segment leds.

#define SEGMENT_DATA_DIR DDRC // Data Direction Register of to the segment selector ports.
#define SEGMENT_PIN PINC  // Input Register of to the segment selector ports.
#define SEGMENT_PORT PORTC // Output Register of the display selector ports, used to multiplex the segment leds.

#define INPUT_DATA_DIR DDRD // Data Direction Register of to the external input ports.
#define INPUT_PIN PIND  // Input Register of to the external input ports, used to interact with the user and read data from the sensors.
#define INPUT_PORT PORTD // Output Register of the external input ports, used to enable pull-up registers.

volatile uint

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>

void initIO(); // Declare function for setting up I/O.
void initTimer(); // Declare function for setting up the timers.
void initInterrupts(); // Declare function for setting up the interrupts.
void checkSwitches(); // Declare function for checking activeswitches.

/**
 * The main program routine and initial starting point of the program.
 */
int main(){
    initIO();
    initTimer();
    initInterrupts();
    while(1){
        asm volatile ("nop"); // Do nothing , No Operation
    }
}

/**
 * This function is for setting up the the I/O registers.
 */
void initIO(){
    DISPLAY_DATA_DIR = 0xff; // Configure the data direction registers for the display ports as outputs.
    SEGMENT_DATA_DIR = 0xff; // Configure the data direction registers for the segment ports as outputs.
    DISPLAY_PORT = 0xFF;
    SEGMENT_PORT = 0xFF;
}

/**
 * This function is for setting up the interrupt control registers.
 */
void initInterrupts(){
    TIMSK = 1 << OCIE1A; // Enable interrupt on timer 1, compare register A
    sei();
}

/**
 * This function is for setting up the timer registers.
 */
void initTimer(){
    TCCR1B |= 1<< WGM12; // Enable Timer 1 waveform modes.
    OCR1A = 15624; // Count to 1 second before triggering an interrupt. (freq / (MCU freq / Prescaler) = (1 / (1 000 000 / 64 ) = 15624
    TCCR1B |= 1 << CS10 | 1 << CS11; // Enable timer 1 from an internal clock source and prescaler of 64.
    TCCR0 =
}

void checkSwithes(){
    if(bit_is_clear(PIND, 0))
    {
        pressed_Confidence_level ++;
        if(pressed == 0)
        {
            PORTD ^= 1 << PIND0;
            PORTD ^= 1 << PIND2;
            pressed = 1;
        }
        else
        {
            Released_confidence_level ++;
            pressed = 0;
        }
    }
}

ISR(TIMER1_COMPA_vect){
    DISPLAY_PORT ^= (1<<7); // Toggle led.
}

