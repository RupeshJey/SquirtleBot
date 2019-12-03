// Created by Rupesh Jeyaram and Iman Wahle
// Final Assignment -- ME 129
// Created 11/15/19


#ifndef Ultron_h
#define Ultron_h

#include "Ultrasonic.h"

#define OW_THRESH 10
#define DW_THRESH 10

class Ultron {
  private: 
	  Ultrasonic dwus_arr[4]; // downward ultrasonics
	  Ultrasonic owus_arr[4]; // outward ultrasonics
	
  public:
    Ultron();
    void init(int (&dw_pin_arr)[4][2], int (&ow_pin_arr)[4][2]);
    float* read_dw_data();
    float* read_ow_data();
    bool is_ow_safe();
    bool is_dw_safe();
    bool is_dw_left_safe();
    bool is_dw_right_safe();
    
};

#endif
