#ifndef Imu_h
#define Imu_h

#include <SparkFun_ADXL345.h>

class Imu {
  private:
  	ADXL345 adxl; 

  public:
    Imu();
    float get_fincline();
};

#endif
