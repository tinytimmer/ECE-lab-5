// switch is used silence the chirping system, which pwm.cpp is in charge of
#include "switch.h"
#include <avr/io.h>

//Initializes pull-up resistor on PD0 and sets it into input mode
void initSwitchPB3(){
    // set direction for input, pin 50 on board
    DDRB &= ~(1 << PORTB3);
    // enable the pullup resistor for stable input
    PORTB |= (1 << PORTB3);

    // enable the interrupt on the switch. From previous labs/lectures
    // enable PCINT 0 - 7
    PCICR |= (1 << PCIE0); 
    // enable PCINT3 since we're using switch 3
    PCMSK0 |= (1 << PCINT3); 
}