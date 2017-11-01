/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 31-10-2017 19:16
 * License: GPLv3 - General Public License version 3
 */
#include <avr/io.h>
#include <avr/interrupt.h>

int main (void)
{
    DDRD |= (1 << 5); // Set LED as output
    TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode
    TCCR1A |= (1 << COM1A0); // Enable timer 1 Compare Output channel A in toggle mode
    OCR1A   = 15624; // Set CTC compare value to 1Hz at 1MHz AVR clock, with a prescaler of 64
    TCCR1B |= ((1 << CS10) | (1 << CS11)); // Start timer at Fcpu/64

    while(1){
        asm volatile ("nop"); // Do nothing , No Operation
    }
}