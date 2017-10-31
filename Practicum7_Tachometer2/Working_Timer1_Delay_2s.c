/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 31-10-2017 15:31
 * License: GPLv3 - General Public License version 3
 */
#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define DISPLAY_DATA_DIR DDRA
#define SEGMENT_DATA_DIR DDRC
#define CONTROL_DATA_DIR DDRD
#define DISPLAY_OUTPUT_PORT PORTA
#define SEGMENT_OUTPUT_PORT PORTC
#define CONTROL_INPUT_PIN PORTD

volatile uint16_t overflowCounter = 0;

int main(){
    DISPLAY_DATA_DIR |= 0xff;
    DISPLAY_OUTPUT_PORT = 0xff;
	
    TCCR1B |= (1 << CS10) | (1<<CS11);
	
	for(;;){
		if (TCNT1 >= 15624)
        {
            DISPLAY_OUTPUT_PORT ^= (1<<7);
            TCNT1 = 0;
			overflowCounter++;
			
			if( overflowCounter >= 2)
			{
				DISPLAY_OUTPUT_PORT ^= (1<<7);
				overflowCounter = 0;
			}
        }
	}
}
