// Created by Rupesh Jeyaram and Iman Wahle
// Final Assignment -- ME 129
// Created 11/15/19



#ifndef LED_h
#define LED_h

#define RED_PIN 33
#define GREEN_PIN 37
#define BLUE_PIN 35

class LED {

  public:
    LED();
    void init();
    void set_color(bool r, bool g, bool b);

};

#endif
