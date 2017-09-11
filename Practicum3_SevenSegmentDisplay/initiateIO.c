//
// Created by FuckMicrosoft on 10-9-2017.
//

#include "initiateIO.h"

/**
 * Initiate the IO ports
 */
void initiateIO(void)
{
    DDRC |= (1<<PC7); // Set port C1 to for output;
    DDRC |= (1<<PC6); // Set port C2 to for output;
    DDRC |= (1<<PC5); // Set port C3 to for output;
    DDRC |= (1<<PC4); // Set port C4 to for output;
    DDRC |= (1<<PC3); // Set port C5 to for output;
    DDRC |= (1<<PC2); // Set port C6 to for output;
    DDRC |= (1<<PC1); // Set port C7 to for output;
    DDRC |= (1<<PC0); // Set port C8 to for output;
	//PORTC = 0b11111111;
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
