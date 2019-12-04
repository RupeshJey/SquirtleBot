// Created by Rupesh Jeyaram and Iman Wahle
// Final Assignment -- ME 129
// Created 11/15/19



#ifndef Safety_h
#define Safety_h

class Safety {
  private: 
    bool set_safety_leds();
    bool is_armed;
    bool estop_nogo;
    

  public:
    Safety();
    bool can_run();
    void arm_bot(); 
    void init();
};

#endif
