
// Created by Rupesh Jeyaram and Iman Wahle
// Final Assignment -- ME 129
// Created 11/15/19

// Referenced ultrasonic Arduino tutorial

#include "Ultrasonic.h"
#include "math.h"
#include "Arduino.h"


Ultrasonic::Ultrasonic(int (&my_pins)[2], bool downward)
{
  int trig_pin;
  int echo_pin;
  bool downward;
}

void Ultrasonic::init() {
  this->trig_pin = my_pins[0];
  this->echo_pin = my_pins[1];
  pinMode(this->trig_pin, OUTPUT);
  pinMode(this->echo_pin, INPUT);

  this->downward = downward;
}

float Ultrasonic::read_data() {
  
  // send signal
  digitalWrite(this->trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(this->trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(this->trig_pin, LOW);
  
  // listen for signal bounceback
  float dur = pulseIn(this->echo_pin, HIGH);
  float dist = dur*0.034/2;

  return dist;
}
