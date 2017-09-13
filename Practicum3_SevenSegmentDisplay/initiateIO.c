//
// Created by FuckMicrosoft on 10-9-2017.
//

#include "initiateIO.h"

/**
 * Initiate the IO ports
 */
void initiateIO(void)
{
    DDRC = 0xFF; // Initiate all C pins as output pins.
    PORTC = 0xFF; // Enable pull up resistor to avoid trouble.

    DDRD = 0xFF;
    DDRD |= (1<<7); // Set port D1 to for output;
    DDRD |= (1<<6); // Set port D2 to for output;
    DDRD |= (1<<5); // Set port D3 to for output;
    DDRD |= (1<<4); // Set port D4 to for output;
	DDRD |= (1<<3); // Set port D5 to for output;
	DDRD |= (1<<2); // Set port D6 to for output;
	DDRD |= (1<<1); // Set port D7 to for output;
	DDRD |= (1<<0); // Set port D8 to for output;
	//PORTD = 0b00000000;
}
