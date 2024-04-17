
#include "pwm.h"
#include "timer.h"

//Initialize timer for PWM
void initPWMTimer3(){
    
    //Set to fast PWM, 10 bit, with a prescaler of 1. 
    TCCR3A |= (1 << COM3A1) | (1 << WGM31) | (1 << WGM30);
    TCCR3A &= ~(1 << COM3A0);
    TCCR3B |= (1 << WGM32);
    TCCR3B &= ~(1 << WGM33);
    TCCR3B |= (1 << CS30);
    TCCR3B &= ~((1 << CS32) | (1 << CS31));

    //Set duty cycles
    OCR3A = 0;

    DDRE |= (1 << DDE3); //set header pin 5 to output
}

//Set volume level, 0 for no sound. If there is sound, chirp as requested.
void setVolume(int result)
{
    if (result == 0)
        OCR3A = result; 
    else {
        OCR3A = result*10;
        delayMs(100);
        OCR3A = 0;
        delayMs(100);
    }
}
