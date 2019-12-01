
#include "Imu.h"
#include <SparkFun_ADXL345.h>

// get library here: https://learn.sparkfun.com/tutorials/adxl345-hookup-guide/all#sparkfun-adxl345-library


Imu::Imu() {
	ADXL345 adxl = ADXL345();
	adxl.powerOn(); 

    adxl.setRangeSetting(4);          // Give the range settings
                                      // Accepted values are 2g, 4g, 8g or 16g
                                      // Higher Values = Wider Measurement Range
                                      // Lower Values = Greater Sensitivity

    adxl.setActivityXYZ(0, 1, 0);       // Set to activate movement detection in the axes "adxl.setActivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
    adxl.setActivityThreshold(75);      // 62.5mg per increment   // Set activity   // Inactivity thresholds (0-255)

}

float Imu::get_fincline() {
    int x,y,z;   
    // x: side-side
    // y: forward-backward
    // z: up-down
    this->adxl.readAccel(&x, &y, &z); 
    return y;
}