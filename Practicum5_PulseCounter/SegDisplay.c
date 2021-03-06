/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 10-09-2017 15:35
 * License: GPLv3 - General Public License version 3
 */
#ifndef F_CPU // Setup the clock speed so we delay loops work correct.
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h> // Import to use its I/O configuration macros.
#include <util/delay.h> // Import macros for delaying the execution of an program.

#include "Helpers.h" // Import some helper functions, macros and constants.
#include "SegDisplayEncoding.h" // Import character to segment encoding mapping.

// Implement the seven segment interface.
#include "SegDisplay.h"

#ifndef SEG7_DISPLAY_DISPLAY_PORT // Make sure the seven segment display row pins are defined.
    #warning "No output port for the displays defined, fall back on default D ports"
    #define SEG7_DISPLAY_DISPLAY_PORT PORTA // If not set to the D output pins.
#endif
#ifndef SEG7_DISPLAY_SEGMENT_PORT // Make sure the seven segment display column pins are defined.
    #warning "No output port for display segments defined, fall back on default C ports"
    #define SEG7_DISPLAY_SEGMENT_PORT PORTC // If not set to the C output pins.
#endif

#ifndef SEG7_DELAY_SEGMENT_U_SEC // The amount of time to show the segments when multiplexing.
    #define SEG7_DELAY_SEGMENT_U_SEC 1000
#endif
#ifndef SEG7_DELAY_SWITCH_DISPLAY_U_SEC // The amount of time to
    #define SEG7_DELAY_SWITCH_DISPLAY_U_SEC 0 // If not set it to 1 microseconds.
#endif
#ifndef SEG7_REFRESH_U_SEC // Make sure the seven segment display refresh rate is defined.
    #define SEG7_REFRESH_U_SEC 1 // If not set it to 1 microseconds.
#endif

#ifndef SEG7_DISPLAY_COUNT // Set the amount of segment displays that are connected.
    #define SEG_DISPLAY_COUNT 4 // Default for the expansion circuit.
#endif

/**
 * This array groups the encoded patterns to print them on a 7 segment display.
 */
static uint8_t encodedNumbers[16] = {
        SEG7_DISPLAY_NUMBER_0, // Numeric character 0
        SEG7_DISPLAY_NUMBER_1, // Numeric character 1
        SEG7_DISPLAY_NUMBER_2, // Numeric character 2
        SEG7_DISPLAY_NUMBER_3, // Numeric character 3
        SEG7_DISPLAY_NUMBER_4, // Numeric character 4
        SEG7_DISPLAY_NUMBER_5, // Numeric character 5
        SEG7_DISPLAY_NUMBER_6, // Numeric character 6
        SEG7_DISPLAY_NUMBER_7, // Numeric character 7
        SEG7_DISPLAY_NUMBER_8, // Numeric character 8
        SEG7_DISPLAY_NUMBER_9, // Numeric character 9
        SEG7_DISPLAY_NUMBER_10, // Numeric character A
        SEG7_DISPLAY_NUMBER_11, // Numeric character B
        SEG7_DISPLAY_NUMBER_12, // Numeric character C
        SEG7_DISPLAY_NUMBER_13, // Numeric character D
        SEG7_DISPLAY_NUMBER_14, // Numeric character E
        SEG7_DISPLAY_NUMBER_15, // Numeric character F
};

//This array stores the unencoded individual digits of the data to be printed on the 7 segment display.
private int digitsToDisplay[SEG_DISPLAY_COUNT] = {255,255,255,255};
// Settings that affect how the numbers get prefixed on the 7 segment display.
private uint8_t printNumberPrefixMode = SEG7_PREFIX_MODE_ZERO;
// Setting that defines what number base to display on the 7 segment display.
private uint8_t printNumberBaseMode = BASE_DECIMAL;

//Forward declare private functions.
private void rawSetSegments( uint8_t byte );
private void setNumericSegmentValue( uint8_t numericValueIndex );
private void clearSegments();
private void rawSetDisplays( uint8_t byte );
private void setDisplay( int displayIndex );
private void unSetDisplay( int number );
private void clearDisplays();
private void numberToDigitArray( int number, uint8_t base );

/*************************************************************************************************[ Segment manipulation
 * Write an raw byte to the segment ports.
 * @param byte The byte that will be written to the segment port.
 */
void rawSetSegments( uint8_t byte )
{
    SEG7_DISPLAY_SEGMENT_PORT = byte;
}

/**
 * Set an bit pattern to any display that is currently turned on.
 * @param numericIndexValue The number to be displayed on the display{s}
 */
void setNumericSegmentValue( uint8_t numericIndexValue )
{
    SEG7_DISPLAY_SEGMENT_PORT = encodedNumbers[ numericIndexValue % printNumberBaseMode ];
}

/**
 * Decode an digit from the digits to display storage and print it to the segment display.
 * @param digitsIndex The number to be displayed on the display{s}
 */
void setStoredDigitSegments( uint8_t digitsIndex )
{
    SEG7_DISPLAY_SEGMENT_PORT = encodedNumbers[ digitsToDisplay[ digitsIndex ]];
    //SEG7_DISPLAY_SEGMENT_PORT = encodedNumbers[ digitsToDisplay[ digitsIndex ] % printNumberBaseMode ];
}

/**
 * Clear all bit patterns that are currently being displayed on the display(s).
 */
void clearSegments()
{
    SEG7_DISPLAY_SEGMENT_PORT = 0xFF; // Enable pull up resistor.
}

static void writeSegmentSequence( uint8_t segmentByte )
{
    for ( int i = 0; i < 7; ++i )
    {
        // 1111 1110
        //!( segmentByte & ( 1 << i ) )
        SEG7_DISPLAY_SEGMENT_PORT = 0xFF;
        SEG7_DISPLAY_SEGMENT_PORT = ( !( segmentByte & ( 1 << i ) ) << i );
        _delay_us(10);
    }
}

/*************************************************************************************************[ Display manipulation
 * Set an raw byte to the display port.
 * @param byte The byte that will be written to the display port.
 */
void rawSetDisplays( uint8_t byte )
{
    SEG7_DISPLAY_DISPLAY_PORT = byte;
}

/**
 * Activate an specific seven segment display so it will be available to write data to it.
 * @param displayIndex The displays index on the connected ports.
 */
void setDisplay( int displayIndex )
{
    SEG7_DISPLAY_DISPLAY_PORT = ~( 1 << displayIndex );
}

/**
 * Deactivate an seven segment so it will no longer display any data.
 * @param displayIndex The displays index on the connected ports.
 */
void unSetDisplay( int displayIndex )
{
    SEG7_DISPLAY_DISPLAY_PORT = ~( 0 << ( displayIndex ));
}

/**
 * Deactivates all seven segment displays.
 */
void clearDisplays()
{
    SEG7_DISPLAY_DISPLAY_PORT = 0xFF; // Enable pull up resistor.
}

/*************************************************************************************************[ Helper functions
 * Parse an numeric value to an array with single digits for multiple number bases.
 * @param number The input number to be displayed on the segment displays.
 * @param base The number system base.
 */
void numberToDigitArray( int number, uint8_t base )
{
    uint8_t currentParsingIndex = 0; // The digitsToDisplay array index that will get filled with an new digit.
    while ( number ) {
        digitsToDisplay[ currentParsingIndex++ ] = number % base; // Assign the least significant digit to the next array index. ( like: 123 % 10 = 3 )
        number /= base; // Throw the least significant digit away, so shift the value one place to the right. ( like: 123 / 10 = 12 )
    }
	// Edited
	//while( currentParsingIndex < ARRAY_LENGTH(digitsToDisplay) ) // Fill the complete array.
    //{
    //    digitsToDisplay[currentParsingIndex] = 255;
   // }
}

/****************************************************************************************************[ Public functions
 *  Clears all data both the segment ports and the display ports.
 */
void clearSegmentDisplays()
{
    clearDisplays();
    clearSegments();
}

/**
 * Write raw bytes to the segment displays.
 * @param segmentByte The byte for for the segment port.
 * @param displayByte The byte for the display port.
 */
void rawWriteDisplay( uint8_t segmentByte, uint8_t displayByte )
{
    clearSegmentDisplays();
    rawSetDisplays( displayByte ); // (de)Activate the displays.
    rawSetSegments( segmentByte );  // Display the segments.
}

/**
 * Write an numeric value to an specific segment display.
 * @param segmentByte The byte for for the segment port.
 * @param displayByte The byte for the display port.
 */
void numericWriteDisplay( uint8_t numericIndex, uint8_t displayIndex )
{
    //clearSegmentDisplays();
    setDisplay( displayIndex ); // Enable writing to the display.
    setNumericSegmentValue( numericIndex ); // Display the segments.
}

/**
 * Set the number base for printing on the 7 segment displays.
 * @param numberBase The base like: BASE_DECIMAL, BASE_HEXADECIMAL or BASE_OCTAL
 */
void setPrintNumberBaseMode( uint8_t numberBase )
{
    printNumberBaseMode = numberBase;
}

/**
 * Use this to define how you want to prefix your numbers printed on the 7 segment display.
 * @param numberPrefixing The prefix to use when printing like: SEG7_PREFIX_MODE_ZERO = 0018 with leading zeros or
 * SEG7_PREFIX_MODE_HEX = 0xFF with the 0x notation.
 */
void setPrintNumberPrefixMode( uint8_t prefixMode )
{
    printNumberPrefixMode = prefixMode;
}

/**
 * Write an number to the connected segmented displays.
 * @param numberToBeDisplayed
 */
void writeNumbersToSegmentDisplays( int numberToBeDisplayed )
{
    // Split the integer passed into an array containing digits that will get passed to each display.
    numberToDigitArray( numberToBeDisplayed, printNumberBaseMode );
    clearSegmentDisplays();

    // Use multiplexing to write different numbers on different displays. Quickly refresh each display
    // from left to right to make it seem that all displays are constantly on.
    for ( int displayCounter = 0; displayCounter < SEG_DISPLAY_COUNT; displayCounter++ ) {
        // Set the correct display to high so we can write segments to it.
        setDisplay( displayCounter );
        // Get the value for the current display from the digitToDisplay array and write the segments.
        setNumericSegmentValue( digitsToDisplay[ displayCounter ] );
        // Display the segments for a few micro seconds, then turn off the display and move to the next.
        _delay_us( SEG7_DELAY_SEGMENT_U_SEC );
        //delayMicroSeconds( SEG7_DELAY_SEGMENT_U_SEC );
        unSetDisplay( displayCounter );
    }
}

/**
 * Count up with an certain interval in milliseconds.
 * @param updateInterval The time it displays an value on the displays.
 */
void countUp( uint16_t updateInterval )
{
    clearSegmentDisplays();
    uint16_t numberCounter = 0; // Used to track what value to print.
    uint64_t iterationCounter = 0; // Used to count iterations, an iteration cost 1000 micro seconds.

    while ( THE_UNIVERSE_HASNT_ENDED ) {
        // Use multiplexing to print data to the displays.
        for ( int activeDisplay = 0; activeDisplay < 4; activeDisplay++ ) {
			if( digitsToDisplay[ activeDisplay] < 20 )
			{
				setDisplay( activeDisplay ); // Activate the display.
				setStoredDigitSegments( activeDisplay );
			}
			_delay_us( 1000 );
            
            if ( iterationCounter > updateInterval/10 ) {
                numberToDigitArray( numberCounter++, printNumberBaseMode );
                iterationCounter = 0;
            }
            // Increment the
            iterationCounter++;
        }
    }
}