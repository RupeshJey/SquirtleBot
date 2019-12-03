// Created by Rupesh Jeyaram and Iman Wahle
// Final Assignment -- ME 129
// Created 11/15/19



#ifndef Ultrasonic_h
#define Ultrasonic_h

class Ultrasonic {
  private: 
    int trig_pin;
    int echo_pin;

  public:
  	bool downward; // true = downward, false = outward
    Ultrasonic();
    void init(int (&my_pins)[2], bool downward);
    float read_data();

};

#endif
