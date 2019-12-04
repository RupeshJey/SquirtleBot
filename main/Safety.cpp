
// Created by Rupesh Jeyaram and Iman Wahle
// Final Assignment -- ME 129
// Created 12/4/19

#include "Safety.h"
#include "LED.h"
#include "Arduino.h"

LED led; 

Safety::Safety()
{
  Serial3.begin(38400);
  bool is_armed;
  bool estop_nogo; 
  led.init();
}

void Safety::init() {
  this->estop_nogo = true; 
  this->is_armed = false;
}

bool Safety::set_safety_leds() {
  if (estop_nogo) {
    led.set_color(1, 0, 0);
  }
  else {
    led.set_color(0, 1, 0);
  }
}

bool Safety::can_run() {

  int incomingByte; 

  if (Serial3.available() > 0) {
    incomingByte = Serial3.read();  

    if (incomingByte == 0) {
      estop_nogo = false; 
    }
    else {
      estop_nogo = true; 
    }
  }

  set_safety_leds();

  return (is_armed && !estop_nogo); 
  
}

void Safety::arm_bot() {
  this->is_armed = true; 
}
