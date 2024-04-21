
#include "pwm.h"
#include "timer.h"

//Initialize timer for PWM
void initPWMTimer3(){
    //Set timer 3 to fast PWM, 10 bit, with a prescaler of 1. 
    TCCR3A |= (1 << WGM31) | (1 << WGM30);
    TCCR3B |= (1 << WGM32) | (1 << WGM33);

    //fast pwm non-inverting mode
    TCCR3A &= ~(1 << COM3C0);
    TCCR3A |= (1 << COM3C1);

    //set prescaler to 1
    TCCR3B |= (1 << CS40);
    TCCR3B &= ~((1 << CS41) | (1 << CS42));

    //set header pin 5 (OC3A) to output 
    DDRE |= (1 << DDE5); 
}

//Set volume level, 0 for no sound. If there is sound, chirp as requested.
void changeFrequency(int freq)
{
    if (freq == 0) { //Turn of chirping. 
        OCR3CH = 0x00;
        OCR3CL = 0x00;
    } else { //Chirp. 
        OCR3AH = ((16000000 / freq) >> 8);
        OCR3AL = (16000000 / freq);

        OCR3CH = OCR3AH >> 1;
        OCR3CL = OCR3AL >> 1;
    }
}
