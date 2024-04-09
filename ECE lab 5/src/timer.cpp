
#include "timer.h"
#include <avr/io.h>

void initTimer1()
{
    // set timer 1 to fast pwm ocr1a as top
    // TCCR1A &= ~(1 << WGM11 | 1 << WGM10);
    TCCR1B |= (1 << WGM12 | 1 << WGM11 | 1 << WGM10);
    TCCR1B &= ~(1 << WGM13);
}

void delayMs(unsigned int delay)
{
    unsigned int i = 0;
    while (i < delay)
    {
        if (TIFR1 & (1 << OCF1A))
        {                          // if flag raised(1 ms)
            TIFR1 |= (1 << OCF1A); // clear flag
            i++;
        }
    }
}