
// Created by Rupesh Jeyaram and Iman Wahle
// Final Assignment -- ME 129
// Created 11/15/19

// Referenced ultrasonic Arduino tutorial

#include "Ultron.h"
#include "math.h"
#include "Arduino.h"
#include "Ultrasonic.h"




Ultron::Ultron()
{
  Ultrasonic us_arr[2]; // make this variable later
}

void Ultron::init(int (&pin_arr)[2][2]) {
  for (int i; i < 2; i++) {
    Ultrasonic us_new;
    us_new.init(pin_arr[i]);
    us_arr[i] = (us_new);
  }
}

float* Ultron::read_data() {

  float* data_pkg = new float[2];
  for (int i = 0; i < 2; i++) {
    data_pkg[i] = us_arr[i].read_data();
  }
  return data_pkg;
}
