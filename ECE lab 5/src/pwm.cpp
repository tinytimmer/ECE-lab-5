
#include "pwm.h"
#include <Arduino.h>

void initTimer3(){
    DDRH |= (1 << PORTH5);//this is pin 8 on board
    DDRH |= (1 << PORTH6);//this is pin 9 on board

    PORTH |= (1 << PORTH5);
    PORTH &= ~(1 << PORTH6);

    DDRE |= (1 << PORTE4); //PORTE4 is pin 2 on the board //OC3B

    TCCR3A |= (1 << WGM30);
    TCCR3A |= (1 << WGM31);
    TCCR3B |= (1 << WGM32);
    TCCR3B |= (1 << WGM33);

    TCCR3A &= ~(1 << COM3C0); //non-inverting mode
    TCCR3A |= (1 << COM3C1);
    TCCR3A &= ~(1 << COM3B0);
    TCCR3A |= (1 << COM3B1);
    TCCR3A &= ~(1 << COM3A0);
    TCCR3A |= (1 << COM3A1);

    TCCR3B |= (1 << CS30); //prescaler
    TCCR3B &= ~(1 << CS31);
    TCCR3B &= ~(1 << CS32);

    //PWM frequency
    OCR3A = 15999;

    //duty cycle
    OCR3B = 15999*0.55;
  
}

void PWMoff(){
    TCCR3B &= ~(1 << CS30); //prescaler
    TCCR3B &= ~(1 << CS31);
    TCCR3B &= ~(1 << CS32);
}

void change_duty(float duty){
    OCR3B = 15999*duty;
    //use this to check if its printing the correct duty change
    //Serial.println(OCR3B);
    //Serial.flush();
}

void turn_right(){
    PORTH |= (1 << PORTH5);
    PORTH &= ~(1 << PORTH6);
}

void turn_left(){
    PORTH &= ~(1 << PORTH5);
    PORTH |= (1 << PORTH6);
}