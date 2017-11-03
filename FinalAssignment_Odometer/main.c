/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 19-10-2017 16:28
 * License: GPLv3 - General Public License version 3
 */

#define F_CPU 1000000UL // Oscillator frequency
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

int toerenTeller = 0;
int interruptTeller = 0;
int tpm = 0;
int duizend;
int honderd;
int ten;
int one;
int mode = 1;
int active = 0;
int active2 = 0;
int active3 = 0;
int active4 = 0;
int snelheid;
int maxsnelheid = 80;
int totaalafstand = 0;
int totaalafstandtmp;
long pulsen = 0;
long pulsentmp = 0;
int i;
int test;
int numbers[11] = { //Zet alle mogelijke nummers in een array zodat met de index het nummer kan worden aan geroepen.

        0x7d,0x44,0x7a,0x6e,0x47,0x2f,0x3f,0x64,0x7f,0x6f,0x80 //begint bij 0, gaat door tot 9 en dan als laatste een punt.
};
int displays[4] = { //Zet de displays in een array zodat ze bij index kunnen worden aangeroepen.

        0x08,0x04,0x02,0x01
};
uint8_t isSwitchActive(uint8_t switchNumber){
    return !(PIND &( 1 << switchNumber));
}
/*
 * De externe interrupt, wordt aangeroepen zodra button 2 wordt ingedrukt.
 */
ISR(INT1_vect){
    toerenTeller++; //Verhoog het aantal toeren.
}
/*
 * De interne interrupt, wordt aangeroepen zodra de timer is afgelopen
 */
ISR(TIMER0_OVF_vect)
{
    TCNT0 = 6; // teller 6 maken
    if (++interruptTeller == 500) { //Als de timer 500 keer is afgelopen (na een seconde).
        asm volatile ("nop"); //Zorgt voor betere precisie
        tpm = toerenTeller;//Bereken de toeren per minuut,
        toerenTeller = 0; //Zet het aantal getelde pulsen weer op 0.
        interruptTeller = 0; //Zet het timer aantal weer op 0.
        asm volatile ("nop"); //Zorgt voor betere precisie.
    }
}
/*
 * De main loop
 */
int main(void) {
    //Zet zowel poort C als D als output.
    DDRC = 0xff;
    DDRA = 0xff;
    GICR  = _BV(INT1);  // enable externe interrupt bit INT0
    MCUCR = 1<<ISC11|1<<ISC10;  // neergaande flank ISC01=1 ISC00=0, dus wanneer de button word ingedrukt.
    TCCR0 = _BV(CS01); //| _BV(CS00); // de prescaling is 8
    TCNT0 = 6; // start timer met 6
    TIMSK = _BV(TOIE0);
    sei(); // zet interrupt flag
    //while(1) {
    // displayNumber(tpm); //Geef de huidige toeren waarde weer
    //}
    while(1){
        while(isSwitchActive(0) && active == 0){ //mode veranderen
            mode = mode + 1;

            //_delay_ms(500);
            if(mode >= 5){
                mode = 1;
            }
            active = 1;
        }
        while(!isSwitchActive(0) && active == 1){ //controle om knop te zorgen dat hij niet te snel veranderd
            active = 0;
        }

        while(isSwitchActive(1) && active2 == 0 && mode == 4){  //snelheid +10 als er op de knop wordt gedrukt
            maxsnelheid = maxsnelheid + 10;

            //_delay_ms(500);
            if(maxsnelheid > 300){
                maxsnelheid = 0;
            }
            active2 = 1;
        }
        while(!isSwitchActive(1) && active2 == 1){ //controle om knop te zorgen dat hij niet te snel veranderd
            active2 = 0;
        }

        while(isSwitchActive(2) && active3 == 0 && mode == 4){ //resetknop maxsnelheid
            maxsnelheid = 0;
            active3 = 1;
        }
        while(isSwitchActive(2) && active3 == 0 && mode == 3){ //resetknop dagteller
            pulsentmp = 0;
            active3 = 1;
        }
        while(!isSwitchActive(2) && active3 == 1){ //controle om knop te zorgen dat hij niet te snel veranderd
            active3 = 0;
        }

        while(isSwitchActive(3) && active4 == 0){ //afstand opmeten
            pulsen = pulsen + 1;
            pulsentmp = pulsentmp + 1;
            active4 = 1;
        }
        while(!isSwitchActive(3) && active4 == 1){ //controle om knop te zorgen dat hij niet te snel veranderd
            active4 = 0;
        }

        snelheid = tpm / 100 * 3.6;     //snelheid berekenen

        if(mode == 1){        //snelheid weergeven
            if(snelheid > maxsnelheid){
                for(i=0;i<1000;i++){
                    displayNumber(snelheid);
                }
                for(i=0;i<20000;i++){
                    PORTA = ~0x80;
                    PORTC = ~0x01;
                }
            }else{
                displayNumber(snelheid);
            }
        }
        if(mode == 2){       //totaalafstand weergeven
            if(snelheid > maxsnelheid){
                for(i=0;i<1000;i++){
                    totaalafstand = pulsen / 10000;
                    displayNumber(totaalafstand);
                }
                for(i=0;i<20000;i++){
                    PORTA = ~0x40;
                    PORTC = ~0x01;
                }
            }else{
                totaalafstand = pulsen / 10000;
                displayNumber(totaalafstand);
            }
        }
        if(mode == 3){       //dagafstand weeergeven
            if(snelheid > maxsnelheid){
                for(i=0;i<1000;i++){
                    totaalafstandtmp = pulsentmp / 10000;
                    displayNumber(totaalafstandtmp);
                }
                for(i=0;i<20000;i++){
                    PORTA = ~0x20;
                    PORTC = ~0x01;
                }
            }else{
                totaalafstandtmp = pulsentmp / 10000;
                displayNumber(totaalafstandtmp);
            }
        }
        if(mode == 4){      //maxafstand weergeven
            displayNumber(maxsnelheid);
        }

    }
}

/*
 * Functie voor het weergeven van een getal op een display.
 * number: Het getal om weer te geven.
 * display: Op welk display het getal weergegeven moet worden.
 */
int display(int number, int display) {
    if(mode ==1){  //extra ledje laten branden
        PORTA = ~0x80;
        PORTC = ~0;
        //_delay_ms(1);
    }
    if(mode ==2){  //extra ledje laten branden
        PORTA = ~0x40;
        PORTC = ~0;
        //_delay_ms(1);
    }
    if(mode ==3){  //extra ledje laten branden
        PORTA = ~0x20;
        PORTC = ~0;
        //_delay_ms(1);
    }
    if(mode ==4){  //extra ledje laten branden
        PORTA = ~0x10;
        PORTC = ~0;
        //_delay_ms(1);
    }



    PORTA = ~displays[display]; //Zet de juiste display aan.
    PORTC = ~numbers[number]; //Stuur de byte voor welk nummer er weergegeven moet worden.
    //_delay_ms(1);
}
/*
 * Functie om een nummer, bestaande uit meerdere getallen weer te geven.
 * number: het getal om weer te geven (max 9999).
 */
int displayNumber(int number)
{
    int dis = 3; //Begin bij de juiste display.
    if ( number != 0 && number < 9999 ) //Check of de waarde 0 is en kleiner als het max nummer.
    {
        while ( number ) //Run net zovaak als dat het nummer lang is.
        {
            display( number % 10, dis ); //Bereken het laatste getal van het nummer en geef deze weer op het juise display.
            number /= 10; //Deel het nummer door 10 om zo in de volgende loop het juiste getal als laatste te krijgen.
            dis--; //Verlaag het display nummer om zo door te gaan naar de volgende.
        }
    } else { //Als het nummer wel 0 is of grooter als de max waarde van 9999.
        display( 0, 3 ); //Geef 0 weer op het display
    }
}

