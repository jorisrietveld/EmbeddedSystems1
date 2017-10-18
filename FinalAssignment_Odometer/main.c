/*
 * 07_practicum.c
 *
 * Created: 09-10-2017 10:48:14
 * Author : Jimmy Habing
 */
#define F_CPU 1000000UL // Oscillator frequency

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
			_delay_us(1); // --------------------------------------------------------------------------------------- Sneller laten updaten zodat hij makkelijker een scan kan voltoien over de displays.
        }
		PORTA = 0xff;
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
        tmp = (uint16_t)speed % 10000; // --------------------------------------------------------------------------------------------------------------------------------De display waarde gelimiteerd tot 9999 met modullo zodat je niet te grote waardes kan invoeren.
        
		if ( tmp <= 9 ) { //Lights up display 0
            setDisplay( tmp, 1 );
        } else if ( tmp > 9 && speed <= 99 ) { //Lights up displays 0,1
            setDisplay( tmp, 2 );
        } else if ( tmp > 99 && speed <= 999 ) {//Lights up displays 0,1,2
            setDisplay( tmp, 3 );
        } else if ( tmp > 999 ) {//Lights up displays 0,1,2,3
            setDisplay( tmp, 4 );
        }
	}
}