/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 31-10-2017 18:35
 * License: GPLv3 - General Public License version 3
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#define LED_DATA_DIRECTION DDRA
#define LED_PORT PORTA

// Interrupt Service Routine on Timer 1: compare output compare register A with: Timer 1: Count register
ISR(TIMER1_COMPA_vect)
{
    LED_PORT ^= (1<<7); // Toggle led
}

int main(){
    LED_PORT = LED_DATA_DIRECTION = 0xff; // Enable the data direction register of of the led port to outputs and pull up all ports.
    TCCR1B |= (1 << WGM12 ); // Configure timer 1 for CTC mode, Clear Timer on Compare.
	TIMSK |= (1 << OCIE1A ); // Enable interrupts on register OCR1A with Timer 1, Output Compare Interrupt Enable 1 A 
	sei(); // Set Enable Interupts, Enable global interrupts.
	OCR1A = 15624; // Set CTC compare value to 1Hz at 1MHz AVR clock, with a prescaler of 64,
    TCCR1B |= (1 << CS10) | (1<<CS11); // Enable Timer1 with an prescaler of 64

    while(1){
        asm volatile ("nop"); // Do nothing , No Operation
    }
}


