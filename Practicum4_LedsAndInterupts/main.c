/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 14-09-2017 19:52
 * License: GPLv3 - General Public License version 3
 */
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t state = 0;

/**
 * The Interrupt Service Routine gets executed when the external interrupt 0 is triggered.
 * It will track the state of the leds and update there values accordingly.
 * The values written to the led port:
 * State 1:     1111 1111
 * State 2:     0111 1111
 * State 3:     0011 1101
 * State 4:     1011 1111
 * State 1:     1111 1111
 */
ISR ( INT0_vect )
{
    PORTC = ~( state ^ ( state >> 1 )); // Encode the state to led output signals.
    state++; // Increase state by 1
    state %= 4; // Limit the state to 3
}

Initiate()
{
	// Enable port D2 as input and activate the internal pull up resistor to prevent floating values.
	DDRD = ~(1<<2);
	PORTD = (1<<2);
	
	//DDRD = ~PORTD = (1<<2);
	
	// Enable interrupt 0 in the general interrupt control register.
	GICR = 1 << INT0;
	
	// Set the ISC (Interrupt Sens Control) bits in the MCUCR (MCU control register to listen for an raising edge event.
	MCUCR = 1 << ISC01 | 1 << ISC00;
	// Set enable interrupt to the control register so interrupts are enabled globally.
	sei();
}

/**
 * The access point to the program.
 */
int main()
{
    while(1);
}

