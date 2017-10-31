/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 31-10-2017 17:33
 * License: GPLv3 - General Public License version 3
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#define LED_DATA_DIRECTION DDRA
#define LED_PORT PORTA

int main(){
    LED_PORT = LED_DATA_DIRECTION = 0xff; // Enable the data direction register of of the led port to outputs and pull up all ports.
    TCCR1B |= (1 << WGM12 ); // Configure timer 1 for CTC mode, Clear Timer on Compare.
    OCR1A = 15624; // Set CTC compare value to 1Hz at 1MHz AVR clock, with a prescaler of 64,
    TCCR1B |= (1 << CS10) | (1<<CS11); // Enable Timer1 with an prescaler of 64

    while(1){

        if ( TIFR & (1 << OCF1A )){ // Check if the counter register with the OCR1A regiter. Timer Flag Register, OCF1A Output Compare A Match Flag chanel A
            LED_PORT ^= (1<<7); // Toggle led.
            TIFR = (1 << OCF1A ); // Clear the CTC flag.

        }
    }
}

