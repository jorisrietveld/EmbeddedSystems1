/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 10-09-2017 15:35
 * License: GPLv3 - General Public License version 3
 */
#include "sevenSegmentDisplay.h"

#include "SegmentDisplayPatterns.h"

#define NELEMS( x )  (sizeof(x) / sizeof((x)[0])) // Get array length: array.size / array.element.size = array.length

#ifndef SEG7_DISPLAY_COUNT // Make sure the amount seven segment displays are defined.
    #define SEG_DISPLAY_COUNT 4 // If not set it to 4 displays.
#endif

#ifndef SEG7_DELAY_SEGMENT_U_SEC // Make sure the seven segment display refresh rate is defined.
    #define SEG7_DELAY_SEGMENT_U_SEC 10 // If not set it to 1 microseconds.
#endif

#ifndef SEG7_DELAY_SWITCH_DISPLAY_U_SEC // Make sure the seven segment display refresh rate is defined.
    #define SEG7_DELAY_SWITCH_DISPLAY_U_SEC 0 // If not set it to 1 microseconds.
#endif

#ifndef SEG7_REFRESH_U_SEC // Make sure the seven segment display refresh rate is defined.
    #define SEG7_REFRESH_U_SEC 1 // If not set it to 1 microseconds.
#endif

#ifndef SEG7_DISPLAY_DISPLAY_PORT // Make sure the seven segment display row pins are defined.
    #define SEG7_DISPLAY_DISPLAY_PORT PORTD // If not set to the D output pins.
#endif

#ifndef SEG7_DISPLAY_SEGMENT_PORT // Make sure the seven segment display column pins are defined.
    #define SEG7_DISPLAY_SEGMENT_PORT PORTC // If not set to the C output pins.
#endif

/**
 * Arrays with bit patterns for different number sets.
 */
uint8_t numericSegmentDisplayPatterns[10] = {
        0b10000010, // Numeric character 0
        0b10111011, // Numeric character 1
        0b10000101, // Numeric character 2
        0b10010001, // Numeric character 3
        0b10111000, // Numeric character 4
        0b11010000, // Numeric character 5
        0b11000000, // Numeric character 6
        0b10011011, // Numeric character 7
        0b10000000, // Numeric character 8
        0b10010000, // Numeric character 9
        0b10010000, // Numeric character A
        0b10010000, // Numeric character B
        0b10010000, // Numeric character C
        0b10010000, // Numeric character D
        0b10010000, // Numeric character E
        0b10010000, // Numeric character F
};

/**
 * Arrays with values that will get printed to the displays.
 */
int digitsToDisplay[SEG_DISPLAY_COUNT];

/**
 * Settings that affect how the numbers get rendered on the segment displays. Like
 * prefixes.
 */
uint8_t segDisplayPrefixMode = SEG7_PREFIX_MODE_ZERO;
uint8_t segDisplayPrintBaseMode = BASE_DECIMAL;

/*************************************************************************************************[ Segment manipulation
 * Write an raw byte to the segment ports.
 *
 * @param byte The byte that wil be written to the segment port.
 */
void rawSetSegments( uint8_t byte )
{
    SEG7_DISPLAY_SEGMENT_PORT = byte;
}

/**
 * Set an bit pattern to any display that is currently turned on.
 *
 * @param numericIndexValue The number to be displayed on the display{s}
 */
void setNumericSegmentValue( uint8_t numericIndexValue )
{
    SEG7_DISPLAY_SEGMENT_PORT = numericSegmentDisplayPatterns[numericIndexValue];
}

/**
 * Clear all bit patterns that are currently being displayed on the display(s).
 */
void clearSegments()
{
    SEG7_DISPLAY_SEGMENT_PORT = 0xFF; // Enable pull up resistor.
}

/*************************************************************************************************[ Display manipulation
 * Set an raw byte to the display port.
 *
 * @param byte The byte that will be written to the display port.
 */
void rawSetDisplays( uint8_t byte )
{
    SEG7_DISPLAY_DISPLAY_PORT = byte;
}

/**
 * Activate an specific seven segment display so it will be available to write data to it.
 *
 * @param displayIndex The displays index on the connected ports.
 */
void setDisplay( int displayIndex )
{
    SEG7_DISPLAY_DISPLAY_PORT = ~(1 << displayIndex);
}
/**
 * Deactivate an seven segment so it will no longer display any data.
 *
 * @param displayIndex The displays index on the connected ports.
 */
void unSetDisplay( int displayIndex )
{
    SEG7_DISPLAY_DISPLAY_PORT = ~(0 << (displayIndex));
}

/**
 * Deactivates all seven segment displays.
 */
void clearDisplays()
{
    SEG7_DISPLAY_DISPLAY_PORT = 0xFF; // Enable pull up resistor.
}

/*********************************************************************************[ Simple segment display manipulation
 *  Clears all data both the segment ports and the display ports.
 */
void clearSegmentDisplays()
{
    clearDisplays();
    clearSegments();
}

/**
 * Write raw bytes to the segment displays.
 *
 * @param segmentByte The byte for for the segment port.
 * @param displayByte The byte for the display port.
 */
void rawWriteDisplay( uint8_t segmentByte, uint8_t displayByte )
{
    clearSegmentDisplays();
    rawSetDisplays( displayByte );
    rawSetSegments( segmentByte );
    delayMicroSeconds( SEG7_DELAY_SEGMENT_U_SEC );

    clearSegmentDisplays();
    delayMicroSeconds( SEG7_DELAY_SWITCH_DISPLAY_U_SEC );
}

/**
 * Write an numeric value to an certain segment display.
 *
 * @param segmentByte The byte for for the segment port.
 * @param displayByte The byte for the display port.
 */
void numericWriteDisplay( uint8_t numericIndex, uint8_t displayIndex )
{
    clearSegmentDisplays();
    setDisplay( displayIndex );
    setNumericSegmentValue( ~SEG7_DISPLAY_NUMBER_0 );
    delayMicroSeconds( SEG7_DELAY_SEGMENT_U_SEC );

    clearSegmentDisplays();
    delayMicroSeconds( SEG7_DELAY_SWITCH_DISPLAY_U_SEC );
}


/**
 * Parse an numeric value to an array with single digits for multiple number bases.
 *
 * @param number The input number to be displayed on the segment displays.
 * @param base The number system base.
 */
void numberToDigitArray( int number, uint8_t base )
{
    uint8_t currentParsingIndex = 0; // The digitsToDisplay array index that will get filled with an new digit.

    while ( number ) // While the integer
    {
        digitsToDisplay[ currentParsingIndex++ ] = number % base; // Assign the least significant digit to the next array index. ( like: 123 % 10 = 3 )
        number /= base; // Throw the least significant digit away, so shift the value one place to the right. ( like: 123 / 10 = 12 )
    }
}

/**
 * Set the numer base for printing on the segment displays.
 * @param numberBase The base like: BASE_DECIMAL, BASE_HEXADECIMAL or BASE_OCTAL
 */
void setSegDisplayPrintBaseMode( uint8_t numberBase )
{
    segDisplayPrintBaseMode = numberBase;
}

/**
 * Set the prefix mode for printing on the segment displays. Modes are difined in "./SegmentDisplayPatterns.h"
 * @param numberPrefixing The prefix to use when printing like: SEG7_PREFIX_MODE_ZERO = 0018 with leading zeros or
 * SEG7_PREFIX_MODE_HEX = 0xFF with the 0x notation.
 */
void setSegDisplayPrefixMode( uint8_t numberPrefixing )
{
    segDisplayPrefixMode = numberPrefixing;
}

/**
 * Write an number to the connected segmented displays.
 * @param numberToBeDisplayed
 *//*
void writeNumbersToSegmentDisplays( int numberToBeDisplayed )
{
    intToDigitArray( numberToDisplay ); // Split the integer passed into an array containing digits that will get passed to each display.
    clearSegmentDisplays();

    for(int displayCounter = 0; displayCounter < SEG_DISPLAY_COUNT; displayCounter++)
    {
        setDisplay( displayCounter ); // Set the correct seven segment display to high so we can write segments to it.

        setDecimalSegmentDisplayByte( digitsToDisplay[ displayCounter ] ); // Write segments to all displays that are currently high.
        delayMicroSeconds(SEG_DISPLAY_REFRESH_U_SEC); // Let the display show the segments for a few micro seconds before moving to the next.

        unSetDisplay( displayCounter ); // Unset the display bit so it is low again.
    }
}*/


/**
 * Write an number to the connected segmented displays.
 * @param numberToBeDisplayed
 */
void writeNumbersToSegmentDisplays( int numberToBeDisplayed )
{
	//uint8_t segDisplayPrefixMode = SEG7_PREFIX_MODE_ZERO;
	//uint8_t segDisplayPrintBaseMode = BASE_DECIMAL;
    numberToDigitArray( numberToBeDisplayed, segDisplayPrintBaseMode ); // Split the integer passed into an array containing digits that will get passed to each display.

    //SEG7_DISPLAY_DISPLAY_PORT = 0xFF;
    //SEG7_DISPLAY_SEGMENT_PORT = 0xFF;
	//int something = 0;
	clearDisplays();
    clearSegments();
	
	  for(int displayCounter = 0; displayCounter < 4; displayCounter++)
	  {
		  //PORTD = _BV( displayCounter );
		  setDisplay( displayCounter );
		  
		  //PORTD = ~(1<<displayCounter);
		  //PORTD = (1 << displayCounter );// Right shift the display index.
		  //setDisplay( displayCounter );

          //setNumericSegmentValue(segDisplayPrintBaseMode);
		  // = numericSegmentDisplayPatterns[ digitsToDisplay[displayCounter] ];
		  //setNumericSegmentValue( displayCounter );
		  
		  //delayMicroSeconds( SEG7_DELAY_SEGMENT_U_SEC );
		  //delayMilliSeconds(500);
		  delayMicroSeconds(50);
          clearDisplays();
		  //delayMicroSeconds( SEG7_DELAY_SWITCH_DISPLAY_U_SEC );
		  //numericWriteDisplay( numberToBeDisplayed, displayCounter );
	  }
	/*
    for(int displayCounter = 0; displayCounter < SEG_DISPLAY_COUNT; displayCounter++)
    {
        PORTD = (0 << displayCounter );// Right shift the display index.
        //setDisplay( displayCounter );

        PORTC = SEG7_DISPLAY_NUMBER_0;
		// = numericSegmentDisplayPatterns[ digitsToDisplay[displayCounter] ];
        //setNumericSegmentValue( displayCounter );
		
        delayMicroSeconds( SEG7_DELAY_SEGMENT_U_SEC );
		
        PORTD = 0xFF;
        //delayMicroSeconds( SEG7_DELAY_SWITCH_DISPLAY_U_SEC );
        //numericWriteDisplay( numberToBeDisplayed, displayCounter );
    }
	*/
}

