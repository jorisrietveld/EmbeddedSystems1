/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 31-10-2017 19:50
 * License: GPLv3 - General Public License version 3
 */
#define F_CPU 1000000UL // MCU frequency

#define DISPLAY_DATA_DIR DDRA // Data Direction Register of to the display selector ports.
#define DISPLAY_PIN PINA // Input Register of to the display selector ports.
#define DISPLAY_PORT PORTA // Output Register of the display selector ports, used to multiplex the segment leds.

#define SEGMENT_DATA_DIR DDRC // Data Direction Register of to the segment selector ports.
#define SEGMENT_PIN PINC  // Input Register of to the segment selector ports.
#define SEGMENT_PORT PORTC // Output Register of the display selector ports, used to multiplex the segment leds.

#define INPUT_DATA_DIR DDRD // Data Direction Register of to the external input ports.
#define INPUT_PIN PIND  // Input Register of to the external input ports, used to interact with the user and read data from the sensors.
#define INPUT_PORT PORTD // Output Register of the external input ports, used to enable pull-up registers.

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

uint16_t pulseCounter = 0;
uint16_t interruptTeller = 0;
uint16_t rpm = 0;

uint8_t encodedNumbers[11] = { 0x7d,0x44,0x7a,0x6e,0x47,0x2f,0x3f,0x64,0x7f,0x6f,0x80 }; // Seggment selectors. 
uint8_t displaySelectors[4] = { 0x08,0x04,0x02,0x01 }; // Display selectors.

void initIoRegisters(); // Declare function to initiate the I/O registers.
void initiateTimers(); // Declare function to initiate the Timer registers.
void displayNumber(uint16_t number);
/*
 * De main loop
 */
int main(void) {
    initIoRegisters();
    initiateTimers();
    GICR  = 0xC0;  // enable externe interrupt bit INT0
    MCUCR = 0x02;  // neergaande flank ISC01=1 ISC00=0, dus wanneer de button word ingedrukt.
    sei(); // zet interrupt flag

    while(1) {
        displayNumber(rpm); //Geef de huidige toeren waarde weer
    }
}
void initIoRegisters(){
    DISPLAY_DATA_DIR = 0xFF; // Initiate display output I/O registers.
    SEGMENT_DATA_DIR = 0xFF; // Initiate segment output I/O registers.
}

void initiateTimers(){
    TCCR0 = _BV(CS01); //| _BV(CS00); // de prescaling is 8
    TCNT0 = 6; // Start Timer 0 Counter register with 6
    TIMSK = _BV(TOIE0);
}

/*
 * Count incomming pulses.
 */
ISR(INT0_vect){
    pulseCounter++; //Verhoog het aantal toeren.
}

/*
 * 
 */
ISR(TIMER0_OVF_vect){
    TCNT0 = 6; // teller 6 maken

    if (++interruptTeller == 500) { //Als de timer 500 keer is afgelopen (na een seconde).
        asm volatile ("nop");
        rpm = (pulseCounter / 1.025)/60; //Bereken de toeren per minuut,
        pulseCounter = 0; //Zet het aantal getelde pulsen weer op 0.
        interruptTeller = 0; //Zet het timer aantal weer op 0.
        asm volatile ("nop");
    }
}

/*
 * Activate displays
 */
int display(int encodingsIndex, int displayIndex) {
    SEGMENT_PORT = 0xFF;
    DISPLAY_PORT = ~displaySelectors[displayIndex]; //Zet de juiste display aan.
    SEGMENT_PORT = ~encodedNumbers[encodingsIndex]; //Stuur de byte voor welk nummer er weergegeven moet worden.
}

/**
 * Display an number to the 7 segment diplays.
 */
void displayNumber(uint16_t number){
    uint8_t displayIndex = 3; // Start at display 4.
    if (number != 0 && number < 9999){ // Limit number range
        while(number){ // For each number
            display(number % 10, displayIndex); // Ouput to the displays.
            number /= 10; // Throw away the last digit.
            displayIndex--; // Decrement index.
        }
    } else {
        display(0,3); // Number out of range.
    }
}