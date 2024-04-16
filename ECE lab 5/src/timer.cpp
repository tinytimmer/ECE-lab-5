
#include "timer.h"
#include <avr/io.h>

unsigned int count=0; //used to keep track of how many ms or us have passed

void initTimer1()
{
    TCCR1A &= ~(1 << WGM00); // Set timer to be in CTC mode, quick note this timer should not turn on
    TCCR1A |= (1 << WGM01);
    TCCR1B &= ~(1 << WGM02);

    TCCR1B |= (1 << CS01) | (1 << CS00); // Sets the prescaler to 64
    //Set output compare registers to proper values
    OCR1A = 249; //Set count to 250
}

void delayMs(unsigned int delay){
    unsigned int delayCnt = 0;
    TCNT1 = 0; //starting the timer at 0 instead of some random junk number
    TIFR1 |= (1 << OCF1A); // set compare flag to start timer
    
    while (delayCnt < delay) 
    {
        if (TIFR1 & (1 << OCF1A)) { //increment only while the flag is set
            delayCnt++;
            TIFR1 |= (1 << OCF1A); //re-start timer. will go to 0 before reaching the if statement above
        }
    }
}