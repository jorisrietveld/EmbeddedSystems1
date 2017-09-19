/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 14-09-2017 19:52
 * License: GPLv3 - General Public License version 3
 */
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t state = 0;

/**
 * This function gets executed when the external intrrupt 0 is triggered. It will track the state of the leds
 * and update there values accordingly. The pattern used:
 * 1111 1111
 * 1111 1110
 * 1111 1100
 * 1111 1101
 * 1111 1111
 */
ISR (INT0_vect)
{
    PORTC = ~( state ^ ( state >> 1 )); // Encode the state to led output signals.
    state++; // Increase state by 1
    state %= 4; // Limit the state to 3
}

/**
 * The access point to the program.
 */
int main()
{
    //  Enable port D2 as input and activate the internal pull up resistor.
    DDRD = ~(1<<2);
    PORTD = (1<<2);

    // Initiate port C 1&2 as output ports and turn off the leds.
    DDRC = PORTC = (1<<0) | (1<<1);
    // Enable interrupt 0 in the general interrupt control register.
    GICR = 1 << INT0;
     // Set the interrupt sens control bits in the MCU control register to listen for an raising edge event.
    MCUCR = 1 << ISC01 | 1 << ISC00;
    // Set enable interrupt to the control register so interrupts are enabled globally.
    sei();
    while(1);
}

