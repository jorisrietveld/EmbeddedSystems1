/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 27-09-2017 13:22
 * License: GPLv3 - General Public License version 3
 */

static uint8_t counterMode = 0; //  The mode of the pulse counter
static uint8_t numberBase = 10; // The base the use when counting.
static uint16_t numberToDisplay = 5678;

// Encoded numbers for 7 segment display, where the indexes correspond to the value being displayed. numbers 1 to 10
static uint8_t encodedNumbers[10] = {
        0x82,
        0xbb,
        0x85,
        0x91,
        0b10111000,
        0xd0,
        0xc0,
        0x9B,
        0x80,
        0x90 ,
        0x88,
};

/**
 * Write an encoded segment byte to an certain display.
 * @param  segmentByte The number encoded in an byte to display an number on the display.
 * @param  displayIndex The display to write to.
 */
static void writeSegmentSequence( uint8_t segmentByte, uint8_t displayIndex)
{
    PORTC = ~( 1 << displayIndex ); // Set the correct display.
    PORTA = encodedNumber;
    _delay_ms(20);
    PORTC = PORTA = 0xFF; // Turn off the display and segment ports.
}

/**
 * Write an number with an maximum of 4 digits to the 7 segment display.
 * @param  number The number to be displayed.
 */
static void writeNumbToDisplay(uint16_t number)
{
    uint8_t index = 0; // Tracks the display that is being written on.

    while( number ) // While there is something left of the number to display.
    {
        uint8_t numberIndex = number % numberBase; //  Get the lowest  digit like: 123, get  3 by dividing by the number base and getting the remainder.
        writeSegmentSequence( encodedNumbers[ numberIndex ], index ); // Write the digit to the screen by getting the encoded value.
        number /= numberBase; // Throw away the lowest digit and move on the the next.
        index++; // Increase the display index.
    }
}

int main(void)
{
    DDRA = DDRC = 0xff; // Initiate ports A and C as output ports.
    PORTA = PORTC = 0xff; // Turn off all leds.
    DDRD |= ~(1<<4) | ~(1<<5) | ~(1<<6) | ~(1<<7); // Set ports D [4-7] to be inputs.
    PORTD = (1<<4) | (1<<5) | (1<<6) | (1<<7); // Enable pull up resistors.

    // Enable interrupt 0 in the general interrupt control register.
    GICR = 1 << INT0;
    // Set the interrupt sens control bits in the MCU control register to listen for an raising edge event.
    MCUCR = 1 << ISC01 | 1 << ISC00;
    // Set enable interrupt to the control register so interrupts are enabled globally.
    sei();

    while (1)
    {
        writeNumbToDisplay(numberToDisplay);
        if( counter - previousCount > counterInterval )
        {
            readSwitches();
        }
        numberToDisplay %= 10000;
    }
}
