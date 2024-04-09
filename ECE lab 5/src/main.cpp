// When you can see this in Github and can successfully edit it, please put your name and Net ID
//  Author: Carmen Timmer,
//  Net ID: cvtimmer,
//  Date: 4/8/2024
//  Assignment:     Lab 5
//  if there is a file missing for this lab go ahead and add it in
//----------------------------------------------------------------------//

#include <Arduino.h>
#include <avr/io.h>
#include "timer.h"
#include "pwm.h"
#include "spi.h"
#include "switch.h"
#include "i2c.h"

// states needed to debounce switch and for the 8x8 matrix LEDs

int main()
{
  Serial.begin(9600);
  sei(); // enable global interrupts

  // initialize stuff here
  void initTimer1();
  initSwitchPB3();

  while (1)
  {
    /* code */
  }

  return (0);
}