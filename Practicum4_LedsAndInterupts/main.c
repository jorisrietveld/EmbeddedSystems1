/*
 * Practicum4_LedsAndInterupts.c
 *
 * Created: 11-9-2017 08:43:09
 * Author : FuckMicrosoft
 */ 

#include <avr/io.h>

int main(void)
{
    GICR = (1<<7); // Enable INT0
    MCUCR = (1<<2); // Set INT0 to
    /* Replace with your application code */
    while (1) 
    {
    }
}

