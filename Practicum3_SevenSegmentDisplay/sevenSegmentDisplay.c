/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 10-09-2017 15:35
 * Licence: GPLv3 - General Public Licence version 3
 */
#include "sevenSegmentDisplay.h"

#define NELEMS( x )  (sizeof(x) / sizeof((x)[0])) // Get array length: array.size / array.element.size = array.length

#ifndef SEG7_DISPLAY_COUNT // Make sure the amount seven segment displays are defined.
    #define SEG_DISPLAY_COUNT 4 // If not set it to 4 displays.
#endif

#ifndef SEG7_DELAY_SEGMENT_U_SEC // Make sure the seven segment display refresh rate is defined.
    #define SEG7_DELAY_SEGMENT_U_SEC 1 // If not set it to 1 microseconds.
#endif

#ifndef SEG7_DELAY_SWITCH_DISPLAY_U_SEC // Make sure the seven segment display refresh rate is defined.
    #define SEG7_DELAY_SWITCH_DISPLAY_U_SEC 0 // If not set it to 1 microseconds.
#endif

#ifndef SEG7_REFRESH_U_SEC // Make sure the seven segment display refresh rate is defined.
    #define SEG7_REFRESH_U_SEC 1 // If not set it to 1 microseconds.
#endif

#ifndef SEG7_DISPLAY_SEGMENT_PORT // Make sure the seven segment display row pins are defined.
    #define SEG7_DISPLAY_SEGMENT_PORT PORTD // If not set to the D output pins.
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

        0b, // Numeric character A
        0b, // Numeric character B
        0b, // Numeric character C
        0b, // Numeric character D
        0b, // Numeric character E
        0b, // Numeric character F
};

/**
 * Arrays with values that will get printed to the displays.
 */
int digitsToDisplay[SEG_DISPLAY_COUNT];

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
 * Set an single bit to an specific position of the segment display port.
 *
 * @param bit The bit that will be set true.
 */
void setSegmentDisplayBit( uint8_t bit )
{
    SEG7_DISPLAY_SEGMENT_PORT |= (1 << bit);
}

/**
 * Unset an single bit to an specific position of the segment display port.
 *
 * @param bit The bit that
 */
void unsetSegmentDisplayBit( uint8_t bit )
{
    SEG7_DISPLAY_SEGMENT_PORT |= (0 << bit);
}

/**
 * Set an bit pattern to any display that is currently turned on.
 *
 * @param number The number to be displayed on the display{s}
 */
void setNumericSegmentValue( int numericValueIndex )
{
    SEG7_DISPLAY_SEGMENT_PORT = numericSegmentDisplayPatterns[numericValueIndex];
}

/**
 * Clear all bit patterns that are currently being displayed on the display(s).
 */
void clearSegments()
{
    SEG7_DISPLAY_SEGMENT_PORT = 0x00;
}

/*************************************************************************************************[ Display manipulation
 * Set an raw byte to the display port.
 *
 * @param byte The byte that will be written to the display port.
 */
void rawSetDisplays( uint8_t byte )
{
    SEG7_DISPLAY_SEGMENT_PORT = byte;
}

/**
 * Activate an specific seven segment display so it will be available to write data to it.
 *
 * @param number The displays index on the connected ports.
 */
void setDisplay( int displayIndex )
{
    SEG7_DISPLAY_SEGMENT_PORT = ~(1 << (number));
}
/**
 * Deactivate an seven segment so it will no longer display any data.
 *
 * @param number The displays index on the connected ports.
 */
void unSetDisplay( int number )
{
    SEG7_DISPLAY_SEGMENT_PORT = ~(0 << (number));
}

/**
 * Deactivates all seven segment displays.
 */
void clearDisplays()
{
    SEG7_DISPLAY_SEGMENT_PORT = 0xFF;
}

/**
 * Activate multiple displays at once.
 *
 * @param displayIndexes The indexes of the displays on the connected ports.
 */
void setDisplays( int displayIndexes[] )
{
    for( int iterationCounter = 0; iterationCounter < NELEMS(displayIndexes); iterationCounter++ )
    {
        setDisplay(displayIndexes[iterationCounter]);
    }
}

/**
 * Deactivate multiple displays at once.
 *
 * @param displayIndexes The indexes of the displays on the connected ports.
 */
void unsetDisplays( int displayIndexes[] )
{
    for( int iterationCounter = 0; iterationCounter < NELEMS(displayIndexes); iterationCounter++ )
    {
        unsetDisplay(displayIndexes[iterationCounter]);
    }
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
 * Write an numeric value to an segment certain display.
 *
 * @param segmentByte The byte for for the segment port.
 * @param displayByte The byte for the display port.
 */
void numericWriteDisplay( uint8_t numericIndex, uint8_t displayIndex )
{
    clearSegmentDisplays();
    setDisplay( displayIndex );
    setNumericSegmentValue( numericIndex );
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

    while ( integer ) // While the integer
    {
        digitsToDisplay[ currentParsingIndex++ ] = integer % base; // Assign the least significant digit to the next array index. ( like: 123 % 10 = 3 )
        integer /= base; // Throw the least significant digit away, so shift the value one place to the right. ( like: 123 / 10 = 12 )
    }
}

void writeNumbersToSegmentDisplays( int numberToBeDisplayed, uint8_t baseDisplayMode, uint8_t enableBasePrefix )
{
    intToDigitArray( numberToDisplay ); // Split the integer passed into an array containing digits that will get passed to each display.
    clearDisplay(); // Clear the D ports, just in case.
	clearDisplaySegments(); // Clear the C ports, just in case.
	
	for(int displayCounter = 0; displayCounter < SEG_DISPLAY_COUNT; displayCounter++)
	{
		setDisplay( displayCounter ); // Set the correct seven segment display to high so we can write segments to it.

        setDecimalSegmentDisplayByte( digitsToDisplay[ displayCounter ] ); // Write segments to all displays that are currently high.
        delayMicroSeconds(SEG_DISPLAY_REFRESH_U_SEC); // Let the display show the segments for a few micro seconds before moving to the next.

		unSetDisplay( displayCounter ); // Unset the display bit so it is low again.
	}    
}