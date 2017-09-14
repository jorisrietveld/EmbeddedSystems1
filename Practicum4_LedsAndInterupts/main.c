/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 14-09-2017 19:52
 * Licence: GPLv3 - General Public Licence version 3
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


volatile uint8_t state= 0;

ISR (INT0_vect)
{
	PORTC = ~PORTC;
}

void ledState2()
{
	PORTC = ~(state ^ (state >> 1 ));
	state = ++state % 4;
}

int main(void)
{
    //GICR = (1<<7); // Enable external interrupt 0.
    //MCUCR = (1<<2); // Set set interrupt 0 to falling edge mode.
   // sei(); // Enable all interrupts.
	//DDRC = 0xFF;
	//PORTC = 0xFF;
    //DDRD = 0xff;

    //DDRD = 1 << PD2;		// Set PD2 as input (Using for interupt INT0)
    //PORTD = 1 << PD2;		// Enable PD2 pull-up resistor
    //DDRD = 0xff;
	DDRC = 0xFF;
	DDRD =0x00; 
	PORTD = 0xFF;

    while (1) 
    {
        PORTC = PIND;
	}
}

