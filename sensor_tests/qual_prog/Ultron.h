// Created by Rupesh Jeyaram and Iman Wahle
// Final Assignment -- ME 129
// Created 11/15/19


#ifndef Ultron_h
#define Ultron_h

#include "Ultrasonic.h"


class Ultron {
  private: 
    Ultrasonic us_arr[2];

  public:
    Ultron();
    void init(int (&pin_arr)[2][2]);
    float* read_data();
};

#endif
