#ifndef Imu_Sensor_h
#define Imu_Sensor_h

#include <SparkFun_ADXL345.h>

class Imu_Sensor {
  private:
  	ADXL345 adxl; 

  public:
    Imu_Sensor();
    float get_fincline();
};

#endif
