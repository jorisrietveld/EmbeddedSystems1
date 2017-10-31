/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 31-10-2017 15:31
 * License: GPLv3 - General Public License version 3
 *//**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 31-10-2017 15:31
 * License: GPLv3 - General Public License version 3
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#define LED_DATA_DIRECTION DDRA
#define LED_PORT PORTA

volatile uint16_t msCounter = 0;

int main(){
	LED_PORT = LED_DATA_DIRECTION = 0xff; // Enable the data direction register of of the led port to outputs and pull up all ports.
	TCCR1B |= (1 << CS10) | (1<<CS11); // Enable Timer1 with an prescaler of 64

	while(1){

		if (TCNT1 >= 15624){ // 1 ms
			TCNT1 = 0; // Reset the counter register to 0 to start counting to 1 ms again.
			msCounter++; // Increment the milliseconds tracker variable.

			if( msCounter >= 2){ // 2 Seconds
				LED_PORT ^= (1<<7); // Toggle led.
				msCounter = 0; // Reset the 2 seconds counter.
			}
		}
	}
}
