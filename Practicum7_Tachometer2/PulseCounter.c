/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 29-10-2017 04:06
 * License: GPLv3 - General Public License version 3
 */

// TIMER1 with prescaler clkI/O/1024
#define TIMER1_PRESCALER      (1 << CS12) | (1 << CS10)

// ~15s (4MHz@1024 prescale value)
#define TIMER1_COMPARE_VALUE 0xE4E1

initiatePulseCounter()
{
    TIMSK  |= (1 << TICIE1);                                    // set input capture interrupt enable
    TCCR1A |= (1 << WGM11);                                     // set Fast PWM mode with ICR1 as compare register
    TCCR1B |= (1 << WGM13) | (1 << WGM12) | TIMER1_PRESCALER;   // set Fast PWM mode with ICR1 as compare register
    ICR1H   = (TIMER1_COMPARE_VALUE >> 8);                      // set compare value for interrupt
    ICR1L   = (TIMER1_COMPARE_VALUE & 0xFF);                    // set compare value for interrupt
    sei(); // global interrupt enable
}/******* Sketch to test Input Capture interrupt handling *********************************
functionality: measure length of pulses on the ICP pin with precision of 0.5 microseconds
Show the min and max pulse widths in microseconds on the serial port

**************************************************************************************************************/
#include <stdio.h>      // for verbose debugging using sprintf

#define icpPin 8        // ICP input pin on arduino
#define outPin 2        // output pin that will shadow the input, can be monitored with a scope

// some variables to help see that something is happening in the interrupt handlers
volatile unsigned int Value;     // this stores the current ICR1 value
volatile unsigned int MinValue;
volatile unsigned int MaxValue;
volatile unsigned int Overflows;
volatile unsigned int PulseCount;


/* Overflow interrupt vector */
ISR(TIMER1_OVF_vect){                 // here if no input pulse detected
    Overflows++;                       // incriment overflow count
}


ISR(TIMER1_CAPT_vect){
    TCNT1 = 0;                            // reset the counter
    if( bit_is_set(TCCR1B ,ICES1)){       // was rising edge detected ?
        digitalWrite(outPin,HIGH );      // yes, set our output pin high to mirror the input
    }
    else {                                // falling edge was detected
        Value = ICR1;                    // save the input capture value
        digitalWrite(outPin,LOW );       // set our output pin low to mirror the input
        PulseCount++;
        if(Value < MinValue)             // update min or max values as appropriate
            MinValue = Value;
        if (Value > MaxValue)
            MaxValue = Value;
    }
    TCCR1B ^= _BV(ICES1);                 // toggle bit value to trigger on the other edge
}

void initiatePulseCounter() {
    beginSerial (19200);
    pinMode(outPin, OUTPUT);               // declare the ledPin as an OUTPUT
    pinMode(icpPin, INPUT);                // ICP pin (digital pin 8 on arduino) as input
    MinValue =    30000;                   // Initialise with extreme values
    MaxValue =    0;


    TCCR1A = 0 ;                    // this register set to 0!
    TCCR1B =_BV(CS11);              // NORMAL MODE!!, prescaller 8, rising edge ICP1 - this works
    TCCR1B |= _BV(ICES1);           // enable input capture

    TIMSK1 =  _BV(ICIE1);                         // enable input capture interrupt for timer 1
    TIMSK1 |= _BV(TOIE1);                         // enable overflow interrupt to detect missing input pulses
    Serial.print("Finished setup\r\n");
}

// this loop prints the number of pulses in the last second, showing min and max pulse widths
void loop() {
    char buffer[80];
    // show the captured data, divide pulse widths by 2 to display time in microseconds
    sprintf(buffer,"Got %d pulses: min=%d, max=%d (%d timer overflows)\r\n", PulseCount, MinValue / 2, MaxValue / 2, Overflows);
    Serial.print(buffer);    // send the info to the serial port
    /* reset variables ready for the next reading */
    PulseCount = Overflows = 0; // reset counts
    MinValue =    30000;        // set values to extremes
    MaxValue =    0;

    delay(1000);             // wait 1 second for next update  [/font]
}