/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 09-09-2017 04:35
 * Licence: GPLv3 - General Public Licence version 3
 */

#include "initiateIO.h"

/**
 * Initiate the IO ports
 */
void initiateIO(void)
{
    DDRC |= ( 1<<7 ); // Set port C1 to for output;
    DDRC |= ( 1<<6 ); // Set port C2 to for output;
    DDRC |= ( 1<<5 ); // Set port C3 to for output;
    DDRC |= ( 1<<4 ); // Set port C4 to for output;
    DDRC |= ( 1<<3 ); // Set port C5 to for output;
    DDRC |= ( 1<<2 ); // Set port C6 to for output;
    DDRC |= ( 1<<1 ); // Set port C7 to for output;
    DDRC |= ( 1<<0 ); // Set port C8 to for output;

    DDRD &= ~(1<<7); 	//Set Pin D1 for input
    PORTD |= (1<<7); //Set internal pull-up resistor (after setting pin for input)

    DDRD &= ~(1<<6); 	//Set Pin D2 for input
    PORTD |= (1<<6); //Set internal pull-up resistor (after setting pin for input)

    DDRD &= ~(1<<5); 	//Set Pin D3 for input
    PORTD |= (1<<5); //Set internal pull-up resistor (after setting pin for input)

    DDRD &= ~(1<<5); 	//Set Pin D4 for input
    PORTD |= (1<<5); //Set internal pull-up resistor (after setting pin for input)
}
