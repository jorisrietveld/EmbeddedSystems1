/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 31-10-2017 19:50
 * License: GPLv3 - General Public License version 3
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#define DISPLAY_DATA_DIR DDRA // Data Direction Register of to the display selector ports.
#define DISPLAY_PIN PINA // Input Register of to the display selector ports.
#define DISPLAY_PORT PORTA // Output Register of the display selector ports, used to multiplex the segment leds.

#define SEGMENT_DATA_DIR DDRC // Data Direction Register of to the segment selector ports.
#define SEGMENT_PIN PINC  // Input Register of to the segment selector ports.
#define SEGMENT_PORT PORTC // Output Register of the display selector ports, used to multiplex the segment leds.

#define INPUT_DATA_DIR DDRD // Data Direction Register of to the external input ports.
#define INPUT_PIN PIND  // Input Register of to the external input ports, used to interact with the user and read data from the sensors.
#define INPUT_PORT PORTD // Output Register of the external input ports, used to enable pull-up registers.

volatile uint32_t timerOverflowCount = 0; // Count Timer 1 overflows to measure distance between input signals.
volatile uint16_t microsecondsBetweenPulses = 0; // Amount of microseconds since last external interrupt.
volatile uint8_t overflowsBetweenPulses = 0; // Amount of overflows since last external interrupt.

volatile uint8_t displayBufferIndex = 0; // Current index of the screen buffer that is being displayed on the seven segment displays.
volatile uint8_t screenBuffer[28] = { [0 ...(27)] = 0xFF }; // The screen buffer that is being multiplexed on the displays.

void initRegisters();

int main(){
    TCCR1B |= (1 << WGM12 ); // Configure timer 1 for CTC mode, Clear Timer on Compare.
    TIMSK |= (1 << OCIE1A ); // Enable interrupts on register OCR1A with Timer 1, Output Compare Interrupt Enable 1 A
    sei(); // Set Enable Interrupts, Enable global interrupts.
    OCR1A = 15624; // Set CTC compare value to 1Hz at 1MHz AVR clock, with a prescaler of 64,
    TCCR1B |= (1 << CS10) | (1<<CS11); // Enable Timer1 with an prescaler of 64

    while(1){
        asm volatile ("nop"); // Do nothing , No Operation
    }
}

void initIoRegisters(){
    DISPLAY_DATA_DIR = SEGMENT_DATA_DIR = 0xFF; // Initiate data output I/O registers.
    INPUT_DATA_DIR = 0x0F; // Initiate data input I/O registers.

    DISPLAY_PORT = 0xFF;
	SEGMENT_PORT = 0xFF; // Turn of all segment leds.
    INPUT_DATA_DIR = 0x0F; // Enable pull-up resistors on the external input ports.
}

void initiateTimers(){
    TCCR0 = 1 << CS00; // Initiate Timer 0 for multiplexing the segment displays.
    TCNT0 = 0; // Initiate counter register of Timer 0.
    TCCR1B = 1 << CS10; // Initiate Timer 1 for tracking time between external inputs.
    TCNT1 = 0; // Initiate counter register of Timer 0.
}

void initInterrupts(){
    TIMSK = 1<< TOIE0 | 1 << TOIE1;// Enable overflow interrupt on Timer 0 and Timer 1
    GICR = 1 << INT0; // Enable external interrupts on port D3.

    sei();
}


ISR(TIMER0_OVF_vect)
{
    displayBufferIndex = displayBufferIndex == 27 ? 0 : displayBufferIndex++; // Increment the display index tracker, rotate if it exceeds buffer size.
    DISPLAY_PORT = screenBuffer[ displayBufferIndex ]; // Output 1 segment of an character on the display.
}

ISR(TIMER1_OVF_vect)
{
    // Increment overflow counter.
    timerOverflowCount++;
}

ISR(INT0_vect)
{
    microsecondsBetweenPulses = TCNT1;
    overflowsBetweenPulses = timerOverflowCount;
}


