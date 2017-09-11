/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 09-09-2017 04:35
 * Licence: GPLv3 - General Public Licence version 3
 */
#include "ledPrograms.h"

/**
 * Blink all leds
 * Pattern written to the output pins:
 * 0000 0000	0x00	0
 * 1111 1111	0xFF	255
 */
void ledBlink( uint8_t delay, uint16_t times )
{
    for( int iterator = 0; iterator < times; iterator++ )
    {
        PORTC = 0x00; // Pull all leds low, this will turn the leds on.
        delayMilliSeconds(delay);
        PORTC = 0xFF; // Pull all leds high, this will turn the leds off.
        delayMilliSeconds(delay);
    }
}

/**
 * Slide single led  from the left to the right
 * Pattern written to the output pins:
 * 1111 1110	0x7F	127
 * 1111 1101	0xBF	191
 * 1111 1011	0xDF	232
 * 1111 0111	0xEF	239
 * 1110 1111	0xF7	247
 * 1101 1111	0xFB	251
 * 1011 1111	0xFD	253
 * 0111 1111	0xFE	254
 */
void ledScanLeft(uint8_t delay, uint8_t times )
{
    while(times--)
    {
        uint8_t tracker = 0x01; //Setup starting value
        PORTC = ~tracker; // Output the value to the LED array.
        delayMilliSeconds(delay);

        while(tracker < 0x80)
        {
            tracker <<= 1;	// Left shift bits to activate the next led.
            PORTC = ~tracker;	// Output new values to LEDs
            delayMilliSeconds(delay);
        }
    }
}

/**
 * Expand the led's from the middle two leds to the end of the array expanding on both sides at the same rate.
 * @param delay
 */
void ledExpand(uint8_t delay)
{
	PORTC = 0xff;
    const prog_uint8_t pattern[9] = { // The bitPattern to write, saved on the PROGMEM to save RAM.
		0b11111111,
		0b11100111,
		0b11000011,
		0b10000001,
		0b00000000,
		0b10000001,
		0b11000011,
		0b11100111,
		0b11111111,
	};
	
	for(int i = 0; i < 9; i++)
	{
		 PORTC = pattern[i];	// Output new values to LEDs
		 delayMilliSeconds(delay);
	}
}

/**
 * Slide single led  from the left to the right
 * Pattern written to the output pins:
 * 0111 1111	0x7F	127
 * 1011 1111	0xBF	191
 * 1101 1111	0xDF	232
 * 1110 1111	0xEF	239
 * 1111 0111	0xF7	247
 * 1111 1011	0xFB	251
 * 1111 1101	0xFD	253
 * 1111 1110	0xFE	254
 */
void ledScanRight(uint8_t delay, uint8_t times )
{
    while(times--)
    {
        uint8_t tracker = 0x80;	//Setup starting value
        PORTC = ~tracker; // Output the value to the LED array.
        delayMilliSeconds(delay);
        while(tracker > 0x01) //Shift bits right until 0000 0001 is reached
        {
            tracker >>= 1; // Right shift bits to activate the next led.
            PORTC = ~tracker; // Output new values to LEDs
            delayMilliSeconds(delay);
        }
    }
}

/**
 * Slide an single led from left to right and back.
 * Pattern written to the output pins:
 * 1111 1110	0xFE	254
 * 1111 1101	0xFD	253
 * 1111 1011	0xFB    251
 * 1111 0111	0xF7	247
 * 1110 1111	0xEF	239
 * 1101 1111	0xDF	223
 * 1011 1111	0xBF    191
 * 0111 1111	0x7F	127
 * 1011 1111	0xBF	191
 * 1101 1111	0xDF	232
 * 1110 1111	0xEF	239
 * 1111 0111	0xF7	247
 * 1111 1011	0xFB	251
 * 1111 1101	0xFD	253
 * 1111 1110	0xFE	254
 */
void ledScan( uint8_t delay, uint16_t times, uint8_t inverse )
{
    while(times--)
    {
        uint8_t tracker = 0x01;	//Setup starting value
        PORTC = inverse ? ~tracker : tracker; // Output the value to the LED array.
        delayMilliSeconds(delay);

        // Shift bits to left if tracker is less than 1000 0000
        while(tracker < 0x80)
        {
            tracker <<= 1; // Left shift bits to (de)activate the next led.
            PORTC = inverse ? ~tracker : tracker;	// Output new values to LEDs
            delayMilliSeconds(delay);
        }

        //Shift bits right until 0000 0001 is reached
        while(tracker > 0x01)
        {
            tracker >>= 1; // Right shift bits to (de)activate the next led.
            PORTC = inverse ? ~tracker: tracker; // Output new values to LEDs
            delayMilliSeconds(delay);
        }
    }
}

/**
 * Slide in all leds from left to right and back.
 * Pattern written to the output pins: (inversed)
 * 1111 1110
 * 1111 1100
 * 1111 1000
 * 1111 0000
 * 1110 0000
 * 1100 0000
 * 1000 0000
 * 0000 0000
 * 1000 0000
 * 1100 0000
 * 1110 0000
 * 1111 0000
 * 1111 1000
 * 1111 1100
 * 1111 1110
 * 1111 1111
/************************************************************************/
void ledSlide( uint8_t delay, uint8_t times )
{
    while(times--)
    {
        uint8_t tracker = 0xFF; // Set starting value to 1111 1111
        PORTC = tracker;
        delayMilliSeconds(delay);
        while(tracker > 0x00 )
        {
            tracker <<= 1;		// Left shift bits to activate the next led.
            PORTC = tracker;	// Output new values to LEDs
            delayMilliSeconds(delay);
        }
        tracker = ~tracker;
        while( tracker > 0x00 )
        {
            tracker >>= 1; // Right shift bits to deactivate the next led.
            PORTC = ~tracker;
            delayMilliSeconds(delay);
        }
    }
}

/**
 * Slide in all leds from the right to left and continue sliding until all leds are off
 * 1111 1110
 * 1111 1100
 * 1111 1000
 * 1111 0000
 * 1110 0000
 * 1100 0000
 * 1000 0000
 * 0000 0000
 * 0000 0001
 * 0000 0011
 * 0000 0111
 * 0000 1111
 * 0001 1111
 * 0011 1111
 * 0111 1111
 * 1111 1111
 */
void slideOut( uint8_t delay, uint8_t times )
{
    while(times--)
    {
        uint8_t tracker = 0xFF;
        PORTC = tracker;
        delayMilliSeconds(delay);

        while(tracker > 0x01 )
        {
            tracker <<= 1; // Left shift bits to activate the next led.
            PORTC = tracker; // Output new values to LEDs
            delayMilliSeconds(delay);
        }
        tracker = ~tracker;
        while(tracker > 0x00 )
        {
            tracker <<= 1;	// Left shift bits to deactivate the next led.
            PORTC = ~tracker; // Output new values to LEDs
            delayMilliSeconds(delay);
        }
    }
}
/**
 * Slide in all leds from left to right, then clear and slide in form right to left.
 */
void slideScan( uint8_t delay, uint8_t times )
{
    while(times--)
    {
        uint8_t tracker = 0xFF;
        PORTC = tracker;
        delayMilliSeconds(delay);

        while(tracker > 0x01 )
        {
            tracker <<= 1;		// Left shift bits to activate the next led.
            PORTC = tracker;	// Output new values to LEDs
            delayMilliSeconds(delay);
        }
        tracker = ~tracker;
        while(tracker > 0x00 )
        {
            tracker >>= 1;		// Left shift bits to deactivate the next led.
            PORTC = tracker;	// Output new values to LEDs
            delayMilliSeconds(delay);
        }
    }
}

