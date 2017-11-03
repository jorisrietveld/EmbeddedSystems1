/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 31-10-2017 19:50
 * License: GPLv3 - General Public License version 3
 */
#define F_CPU 1000000UL // MCU frequency

#define DISPLAY_DATA_DIR DDRA // Data Direction Register of to the display selector ports.
#define DISPLAY_PIN PINA // Input Register of to the display selector ports.
#define DISPLAY_PORT PORTA // Output Register of the display selector ports, used to multiplex the segment leds.

#define SEGMENT_DATA_DIR DDRC // Data Direction Register of to the segment selector ports.
#define SEGMENT_PIN PINC  // Input Register of to the segment selector ports.
#define SEGMENT_PORT PORTC // Output Register of the display selector ports, used to multiplex the segment leds.

#define INPUT_DATA_DIR DDRD // Data Direction Register of to the external input ports.
#define INPUT_PIN PIND  // Input Register of to the external input ports, used to interact with the user and read data from the sensors.
#define INPUT_PORT PORTD // Output Register of the external input ports, used to enable pull-up registers.

#include <avr/io.h>
#include <avr/interrupt.h>

uint16_t pulseCounter = 0; // Amount of incomming pulses on INT0
uint16_t interruptCounter = 0; // Amount of timer0 overflows.
uint16_t rpm = 0; // Amount of revolutions per minut.

uint8_t encodedNumbers[11] = { 0x7d,0x44,0x7a,0x6e,0x47,0x2f,0x3f,0x64,0x7f,0x6f,0x80 }; // Seggment selectors. 
uint8_t displaySelectors[4] = { 0x08,0x04,0x02,0x01 }; // Display selectors.

void initIoRegisters(); // Declare function to initiate the I/O registers.
void initiateTimers(); // Declare function to initiate the Timer registers.
void displayNumber(uint16_t number); // Declare function to

/*
 * De main loop
 */
int main(void) {
    initIoRegisters(); // Init I/O
    initiateTimers(); // Init Timers
    GICR  = 0xC0;  // enable externe interrupt bit INT0
    MCUCR = 0x02;  // React to falling edge.
    sei(); // Enable global interrupts.

    while(1) {
        displayNumber(rpm); //Geef de huidige toeren waarde weer
    }
}

/*
 * Count incomming pulses.
 */
ISR(INT0_vect){
    pulseCounter++; //Verhoog het aantal toeren.
}

/**
 * An service routine to update the number to display.
 */
ISR(TIMER0_OVF_vect){
    TCNT0 = 6; // Initiate with 6 ( 256 - 6 = 250 uS )
    if (++interruptCounter == 500) { //  1 second
        asm volatile ("nop");
        rpm = (pulseCounter / 1.025); // calculate revolutions per minut.
        pulseCounter = 0; // Reset the pulse counter.
        interruptCounter = 0; // 
        asm volatile ("nop");
    }
}