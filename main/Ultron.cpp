
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
  Ultrasonic dwus_arr[4]; // downward ultrasonics
  Ultrasonic owus_arr[4]; // outward ultrasonics
}

void Ultron::init(int (&dw_pin_arr)[4][2], int (&ow_pin_arr)[4][2]) {
  // initialize downward ultrasonics
  for (int i; i < 4; i++) {
    Ultrasonic us_new;
    us_new.init(dw_pin_arr[i], true);
    dwus_arr[i] = (us_new);
  }

  // initialize outward ultrasonics
  for (int i; i < 4; i++) {
    Ultrasonic us_new;
    us_new.init(ow_pin_arr[i], false);
    owus_arr[i] = (us_new);
  }
}

float* Ultron::read_dw_data() {

  float* data_pkg = new float[4];
  for (int i = 0; i < 4; i++) {
    data_pkg[i] = dwus_arr[i].read_data();
  }
  return data_pkg;
}

float* Ultron::read_ow_data() {

  float* data_pkg = new float[4];
  for (int i = 0; i < 4; i++) {
    data_pkg[i] = owus_arr[i].read_data();
  }
  return data_pkg;
}

bool Ultron::is_ow_safe() {
  float* data = this->read_ow_data();
  bool safe = true;
  for (int i = 0; i < 4; i++) {
    if (data[i] < OW_THRESH) {
      safe = false;
    }
  }
  return safe;
}

bool Ultron::is_dw_safe() {
  float* data = this->read_dw_data();
  bool safe = true;
  for (int i = 0; i < 4; i++) {
    if (data[i] > DW_THRESH) {
      safe = false;
    }
  }
  return safe;
}

bool Ultron::is_dw_left_safe() {
  float* data = this->read_dw_data();
  bool safe = true;
  for (int i = 0; i < 2; i++) {
    if (data[i] > DW_THRESH) {
      safe = false;
    }
  }
  return safe;

}


bool Ultron::is_dw_right_safe() {
  float* data = this->read_dw_data();
  bool safe = true;
  for (int i = 2; i < 4; i++) {
    if (data[i] > DW_THRESH) {
      safe = false;
    }
  }
  return safe;
  
}
