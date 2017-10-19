/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 13-10-2017 01:39
 * License: GPLv3 - General Public License version 3
 */
#ifndef F_CPU
    #define F_CPU 1000000UL // Oscillator frequency
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

uint8_t i;  // ---------------------------------------------- Verranderd naar een uint8_t het nummer wordt nooit hooger dan 4
uint8_t digit;  // ---------------------------------------------- Verranderd naar een uint8_t het nummer wordt nooit hooger dan 9
uint16_t tmp = 0;  // ---------------------------------------------- Verranderd naar een uint32_t zodat je nummbers van 9999 kan opslaan.
double speed = 0; // ---------------------------------------------- Verranderd naar een double omdat deze floating point nummers moet gaan opslaan.
volatile uint32_t count = 0; //-----------------------------------------------------volatile gemaakt zodat compiler optimalizeties te voorkomen die er voor kunnen zorgen dat de interrupt service routine het variable niet meer kan vinden.
volatile uint8_t interruptcount = 0; //-----------------------------------------------------volatile gemaakt zodat compiler optimalizeties te voorkomen die er voor kunnen zorgen dat de interrupt service routine het variable niet meer kan vinden.

ISR (INT0_vect)
{
    //count = count + 1; //Every time a button is pushed or a pulse is received add a value to the count variable
    count++;
}

ISR (TIMER0_OVF_vect)
{
    TCNT0 += 6; //Making the timer 6    256 - 5 = 250

    if ( ++interruptcount == 25 ) {   // Toggled one time = 100ms
        asm volatile ("nop");
        speed = count * 1.24;               // Calculates how many pulses/cycles in 1 second = amount of Hz ?? no calculation needed?
        interruptcount = 0;         // Reset the counter
        asm volatile ("nop");
        count = 0;                  // Reset the count to count the next batch
    }
}

//2D array to instruct each segment of a 7 segment display
int display[10][7] = {
        { 0xDF, 0xBF, 0xFB, 0xF7, 0xEF, 0xFE, 0xFF },     //0
        { 0xBF, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },     //1
        { 0xDF, 0xBF, 0xFD, 0xEF, 0xF7, 0xFF, 0xFF },     //2
        { 0xDF, 0xBF, 0xFD, 0xFB, 0xF7, 0xFF, 0xFF },     //3
        { 0xFE, 0xFD, 0xBF, 0xFB, 0xFF, 0xFF, 0xFF },     //4
        { 0xDF, 0xFE, 0xFD, 0xFB, 0xF7, 0xFF, 0xFF },     //5
        { 0xDF, 0xFB, 0xF7, 0xEF, 0xFE, 0xFD, 0xFF },     //6
        { 0xDF, 0xBF, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF },     //7
        { 0xDF, 0xBF, 0xFB, 0xF7, 0xEF, 0xFE, 0xFD },     //8
        { 0xDF, 0xBF, 0xFB, 0xF7, 0xFE, 0xFD, 0xFF },     //9
};

// Method to display the current number and on how many displays
void setDisplay( int tmp, int dsplAmount )
{
    for ( i = 0; i < dsplAmount; i++ ) {
        digit = tmp % 10;
        tmp = tmp / 10;
        PORTB = ~_BV( i ) & 0x0F;

        for ( int j = 0; j < 7; j++ ) {
            PORTA = display[ digit ][ j ];
			_delay_us(10); // --------------------------------------------------------------------------------------- Sneller laten updaten zodat hij makkelijker een scan kan voltoien over de displays.
        }
		PORTA = 0xff; // ---------------------------------- Verranderd zodat het scherm altijd leeg is voor je gaat schrijven anders krijg je rare segmenten zoals de middelste van het nummer 8 die feller is.
    }
}

int main( void )
{

    DDRA = 0xFF;
    DDRB = 0x0F;
    DDRD = 0x00;

    GICR = _BV( INT0 );    // Enable external interrupt bit INT0
    MCUCR = _BV( ISC00 );   // Enable interrupt reaction

    sei();                // Enable interrupts in general

    TCCR0 = _BV( CS01 ) | _BV( CS00 );  // Prescaling is 64
    TCNT0 = 6;                      // Start timer with 6
    TIMSK = _BV( TOIE0 );             // interrupt timer0 overflow

    while ( 1 ) {
        //Control structure to light up only certain displays when there is a value > 9
		PORTB = 0xff;
		PORTA = 0xff;
		_delay_ms(1000);
		PORTB = 0x00;
		PORTA = 0x00;
		_delay_ms(1000);
	}
}