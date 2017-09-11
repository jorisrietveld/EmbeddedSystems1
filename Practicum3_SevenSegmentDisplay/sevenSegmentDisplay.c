/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 10-09-2017 15:35
 * Licence: GPLv3 - General Public Licence version 3
 */
#include "sevenSegmentDisplay.h"

uint8_t sevenSegmentDisplayNumbers[10] =
        {
                0b10000010,
                0b10111011,
                0b10000101,
                0b10010001,
                0b10111000,
                0b11010000,
                0b11000000,
                0b10011011,
                0b10000000,
                0b10010000,
        };

uint8_t digitsToDisplay[4]  = {1,2,3,4};

void activateNumberDisplay( uint8_t number )
{
	
}

void displaysNumber( uint8_t number )
{
    PORTC = sevenSegmentDisplayNumbers[number];
}

void splitInteger( uint8_t integer )
{
    digitsToDisplay[0] = (int)(integer / 1000);
    integer -= digitsToDisplay[0];
    digitsToDisplay[1] = (int)integer / 100;
    integer -= digitsToDisplay[1];
    digitsToDisplay[2] = (int)integer / 10;
    integer -= digitsToDisplay[2];
    digitsToDisplay[3] = (int)integer;
	//digitsToDisplay = {1,2,3,4};
}


void writeToDisplay( uint16_t numberToDisplay )
{
    splitInteger(numberToDisplay);
	
	for(int displayCounter = 0; displayCounter < 5; displayCounter++)
	{
		PORTD = ~(1<<displayCounter);
		PORTC = sevenSegmentDisplayNumbers[ digitsToDisplay[displayCounter] ];
		_delay_us(50);
		PORTD = ~(0<<displayCounter);
	}
/*
    for( uint8_t displayCounter = 0; displayCounter < 4; displayCounter++ )
    {
		if( displayCounter == 0)
		{
			PORTD = 0b000000001;
		}
		else if( displayCounter == 1)
		PORTD = 0b00000000;
		//PORTD = _BV(displayCounter);//(1 << displayCounter );
		PORTD = ( 1 << displayCounter+4 );
		//PORTD = ~0b00000010;
        //activateNumberDisplay( displayCounter );
		//PORTC = 0b10000010;
		PORTC = sevenSegmentDisplayNumbers[displayCounter];
        //displaysNumber( digitsToDisplay[displayCounter] );
		PORTD = 0b00000000;
		delayMilliSeconds(1);
    }*/
    
}