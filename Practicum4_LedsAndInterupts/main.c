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
 * State 0:     1111 1111
 * State 1:     0111 1111
 * State 2:     0011 1101
 * State 3:     1011 1111
 * State 0:     1111 1111
 */
ISR ( INT0_vect )
{
	// Encode the state to led output signals.
	// Encoding pattern:
	// [ State 0 ]
	//  (0000 0000 >> 1)        == 0000 0000
	//  0000 0000 XOR 0000 0000 == 0000 0000
	// ~0000 0000               == 1111 1111
	// [ State 1 ]
	//  (0000 0001 >> 1)        == 0000 0000
	//  0000 0001 XOR 0000 0000 == 0000 0001
	// ~0000 0000               == 1111 1110
	// [ State 2 ]
	//  (0000 0010 >> 1)        == 0000 0001
	//  0000 0010 XOR 0000 0001 == 0000 0011
	// ~0000 0011               == 1111 1100
	// [ State 3 ]
	//  (0000 0011 >> 1)        == 0000 0001
	//  0000 0011 XOR 0000 0001 == 0000 0010
	// ~(0000 0010)             == 1111 1100
    PORTC = ~( state ^ ( state >> 1 ));

	// Increase the state coutner and flip over when the 4th state is reached.
    state++;
    state %= 4;
}

initiate()
{
	// Enable port D2 as input and activate the internal pull up resistor to prevent floating values.
	DDRD = ~(1<<2);
	PORTD = (1<<2);
	
	//DDRD = ~PORTD = (1<<2);
	
	// Enable interrupt 0 in the general interrupt control register to listen for button presses.
	GICR = 1 << INT0;
	
	// Set the ISC (Interrupt Sens Control) bits in the MCUCR (MCU control register to listen for an raising edge event.
	MCUCR = ( 1<<ISC01) | ( 1<<ISC00 );
	
	// Set enable interrupt to the control register so interrupts are enabled globally.
	sei();
}

/**
 * The access point to the program.
 */
int main()
{
	initiate(); // Initiate the internal registers.
    while(1); // Loop until the head death of the universe occurs.
}

