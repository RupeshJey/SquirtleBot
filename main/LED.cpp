
// Created by Rupesh Jeyaram and Iman Wahle
// Final Assignment -- ME 129
// Created 11/15/19

// Referenced ultrasonic Arduino tutorial

#include "LED.h"
#include "Arduino.h"


LED::LED()
{
  
}

void LED::init() {
  pinMode(RED_PIN, OUTPUT); 
  pinMode(GREEN_PIN, OUTPUT); 
  pinMode(BLUE_PIN, OUTPUT); 
}

void LED::set_color(bool r, bool g, bool b) {
  
  digitalWrite(RED_PIN, r);
  digitalWrite(GREEN_PIN, g);
  digitalWrite(BLUE_PIN, b);
}
