#ifndef PWM_H
#define PWM_H

#include <avr/io.h>

void initTimer3();
void PWMoff();
void change_duty(float duty);
void turn_right();
void turn_left();

#endif