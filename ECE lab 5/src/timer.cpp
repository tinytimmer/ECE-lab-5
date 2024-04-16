
#include "timer.h"
#include <avr/io.h>

unsigned int count=0; //used to keep track of how many ms or us have passed

void initTimer1()
{
    //setting time1 up in CTC mode
    TCCR1A &= ~(1 << WGM10);
    TCCR1A &= ~(1 << WGM11);     
    TCCR1B |= (1 << WGM12);
    TCCR1B &= ~(1 << WGM13);
}

void delayMs(unsigned int delay)
{
    //set up prescaler of 1024
    //this also starts the timer
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS11);
    TCCR1B &= ~(1 << CS12);

    OCR1A = 250;//number of counts for a us

    TCNT1 = 0; //initialize counter to 0
    count = 0; //look at description for ms delay

    TIFR1 |= (1 << OCF1A); //puts the timer interrupt flag down

    //at this point our timer is counting and when it reaches the value
    //in the OCR0A register the TIFR0 flag will go up

    while(count < delay) //until we have waited the desired amount of us
    {
        if(TIFR1 & (1 << OCF1A)) //if we have reached our allotted time to set the flag again
        {
            count++;
            TIFR1 |= (1 << OCF1A); //reset the timer interrrupt flag to 0.
        }
    }

    //turn the timer off
    TCCR1B &= ~(1 << CS10);
    TCCR1B &= ~(1 << CS11);
    TCCR1B &= ~(1 << CS12);

}