/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Author: Randy Dijskhoorn <radijkshoorn@gmail.com>
 * Created: 05-11-2017 10:24
 * License: GPLv3 - General Public License version 3
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>

#define DISPLAY_DATA_DIR DDRA // Data Direction Register of to the display selector ports.
#define DISPLAY_PIN PINA // Input Register of to the display selector ports.
#define DISPLAY_PORT PORTA // Output Register of the display selector ports, used to multiplex the segment leds.
#define SEGMENT_DATA_DIR DDRC // Data Direction Register of to the segment selector ports.
#define SEGMENT_PIN PINC  // Input Register of to the segment selector ports.
#define SEGMENT_PORT PORTC // Output Register of the display selector ports, used to multiplex the segment leds.
#define INPUT_DATA_DIR DDRD // Data Direction Register of to the external input ports.
#define INPUT_PIN PIND  // Input Register of to the external input ports, used to interact with the user and read data from the sensors.
#define INPUT_PORT PORTD // Output Register of the external input ports, used to enable pull-up registers.

volatile uint64_t distanceTraveledCm = 0; // The amount of centimeters the car traveled.
volatile uint16_t centimetersPerSecond = 0; // Amount of cm traveled in the last second.
volatile uint16_t milliseconds = 0; //The amount of milliseconds since the last overflow.
volatile uint16_t millisecondsOverflow = 0; // The amount of overflows since the meter is turned on.

uint32_t lastButtonCheckTime = 0; // The time stamp of last button check call.
uint8_t buttonCheckInterval = 30; // The interval of calling the button check function.
uint8_t lastButtonState = 0;
uint8_t mode = 0;

uint16_t currentDrivingSpeed = 0; // The current driving speed of the car in kilometers per hour.
uint64_t distanceTraveled = 0;
uint64_t dayCounter = 0;

uint16_t drivingSpeedAlert = 0;

void initIO(); // Declare function for setting up I/O.
void initTimer(); // Declare function for setting up the timers.
void initInterrupts(); // Declare function for setting up the interrupts.
void checkButtons(); // Declare function for checking active witches.
uint32_t getMilliseconds(); // Declare function for getting the current milliseconds since the last reset.
void clearMilliseconds(); // Declare function for resetting the milliseconds count.
void updateMaximumDrivingSpeed(); // Declare function for updating the maximum driving speed.
void resetDayCounter(); // Declare function for resetting the day counter.
uint64_t getDayCounterValue(); // Declare function for getting the display value of the day counter.
uint64_t getDistanceCounterValue(); // Declare function for getting the display value of the distance counter.

/**
 * The main program routine and initial starting point of the program.
 */
int main(){
    initIO();
    initTimer();
    initInterrupts();
    while(1){
        asm volatile ("nop"); // Do nothing , No Operation

        if( getMilliseconds() - lastButtonCheckTime > buttonCheckInterval ) { // Check the button state every 10 milliseconds.
            lastButtonCheckTime = getMilliseconds(); // Save the current check time.
            checkButtons(); // Check the button state.
        }
        DISPLAY_PORT = ~(1 << mode+4);
    }
}

/**
 * This function is for setting up the the I/O registers.
 */
void initIO(){
    DISPLAY_DATA_DIR = 0xff; // Configure the data direction registers for the display ports as outputs.
    SEGMENT_DATA_DIR = 0xff; // Configure the data direction registers for the segment ports as outputs.
    DISPLAY_PORT = 0xFF;
    SEGMENT_PORT = 0xFF;
}

/**
 * This function is for setting up the interrupt control registers.
 */
void initInterrupts(){
    TIMSK |= 1 << OCIE1A; // Enable interrupt on timer 1, compare register A
    TIMSK |= 1 << TOIE0; // Enable interrupt on timer 0 overflow.
    GICR  = INT0;  // enable externe interrupt bit INT0
    MCUCR = ISC01;  // React to falling edge.
    sei();
}

/**
 * This function is for setting up the timer registers.
 */
void initTimer(){
    TCCR1B |= 1<< WGM12; // Enable Timer 1 waveform modes. (CTC mode) clear timer on compare
    TCCR1B |= 1 << CS10 | 1 << CS11; // Enable timer 1 from an internal clock source and prescaler of 64.
    OCR1A = 15624; // Count to 1 second before triggering an interrupt. (freq / (MCU freq / Prescaler) = (1 / (1 000 000 / 64 ) = 15624

    TCCR0 = 1<<CS01; // Enable timer 0 from the internal clock source and a prescaler of 8.
    // calculate amount of ticks: 1000uS / 8uS = 127 ticks, Calculate initial register value 256 - 127 = 129
    TCNT0 = 129; // Overflow every 1 millisecond.
}

/**
 * Function to get the amount of milliseconds since the last clear.
 * @return
 */
uint32_t getMilliseconds(){
    return (uint32_t )(millisecondsOverflow*65535) + milliseconds;
}

/**
 * Function to clear the current counted milliseconds.
 */
void clearMilliseconds(){
    millisecondsOverflow = 0; // Clear overflow count.
    milliseconds = 0; // Clear milliseconds count.
}

/**
 * This function increases the driving speed alert with 10, if its higher than the maximum of 300 it roles over to 0.
 */
void updateMaximumDrivingSpeed(){
    drivingSpeedAlert += 10; // Increase the driving speed alert with 10.
    drivingSpeedAlert %= 300; // Set an maximum value for the driving speed alert.
}

/**
 * This function resets the value in the day counter.
 */
void resetDayCounter(){
    dayCounter = distanceTraveled;
}

/**
 * Get the current value to display on the day counter.
 * @return The value to display on the day counter.
 */
uint64_t getDayCounterValue(){
    return distanceTraveledCm - dayCounter;
}

uint64_t getDistanceCounterValue(){
    return distanceTraveled;
}

/**
 * This function checks the current state of the buttons. It gets called every 10 milliseconds, it checks if there
 * was an pending button press, if so register it else clear previous button.
 */
void checkButtons()
{
    if(bit_is_clear(PIND, 0)){// Checks if the button on bit one is pressed then
        if (lastButtonState == 1){
            mode++;
            mode %=4;
            lastButtonState=0;
        } else {
            lastButtonState = 1;
        }
    }
    else if(bit_is_clear(PIND, 1)) {// Checks if the button on bit 1 is pressed and mode 3 is on, then resets the daycounter.
        if (lastButtonState == 2 && mode == 3) {
            resetDayCounter();
            lastButtonState = 0;
        } else {
            lastButtonState = 2;
        }
    }
    else if(bit_is_clear(PIND, 3)){
        if (lastButtonState == 3 && mode == 4) {
            updateMaximumDrivingSpeed();
            lastButtonState = 0;
        } else{
            lastButtonState = 3;
        }
    }
}

void displayValueOnScreen(){
    //  mode == 0

    // if mode == 2

    //if mode == 3

    // if mode == 4
}

/**
 * Interrupt service routine for counting pulses from the cars speed sensor.
 */
ISR(INT0_vect){
    distanceTraveledCm++; // Add an other centimeter to the distance tracker.
    centimetersPerSecond++; // Add an other centimeter to the driving speed tracker.
}

/**
 * This service routine is responsible to keep track of the milliseconds since the last clear.
 */
ISR(TIMER0_OVF_vect){
    if(milliseconds == 65535) {
        millisecondsOverflow++;
    }
    milliseconds++;
}

/**
 * This service routine is responsible to calculate the current driving speed.
 */
ISR(TIMER1_COMPA_vect){
    currentDrivingSpeed = centimetersPerSecond* 0.0359999999712; // Calculate driving speed in centimeters per second.
    centimetersPerSecond = 0; // Reset the pulses per second counter.
}

