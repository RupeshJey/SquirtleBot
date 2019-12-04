/*
 * MAIN SQUIRTLEBOT CODE
 * ME/CS/EE 129
 * 
 * Group Members: 
 * Daniel Neamati
 * Iman Wahle
 * Spencer Morgenfeld
 * Nick Clausen
 * Rupesh Jeyaram
 */

// Packages

#include <Pixy2.h>        // Pixy package
#include <PIDLoop.h>      // PID looping

#include "MotorDriver.h"  // Controlling motors
#include "Ultron.h"       // Handle ultrasonic sensors
#include "LED.h"          // Handle LEDs
#include "Safety.h"       // Handle safety components
#include "MPU6050_tockn.h" // IMU
#include <Wire.h>
MPU6050 mpu6050(Wire);

#define ARM_BUTTON_PIN 45

// Decalre component handlers
Ultron ultron;
MotorDriver dt;
LED led_main; 
Safety safety; 
Pixy2 pixy;

// Preprocessor directives -- constants
#define X_CENTER         (pixy.frameWidth/2)
#define BACKUP_CAP 3
#define LINE_CAP 3
#define SHIMMY_BACKUP 500 
#define ARM_DELAY 3000

// Global state variables
bool lf_mode = false;
bool us_mode = true;
bool tictac_mode = false;
bool lf_valid = true; // will turn false once we reach the ramp

// Ultrasonic pin settings 
int dw_pin_arr[4][2] = {{28,29},{24,25},{10,11},{8,9}}; // lf, lb, rf, rb
int ow_pin_arr[4][2] = {{26,27},{22,23},{12,13},{40,41}}; // lf, lb, rf, rb
// bool is_left[4] = {1,1,0,0};
// bool is_front[4] = {1,0,1,0};

//float convert_z(float z) {
//  float newz = z;
//  while (newz <= -180) { newz += 360.0; }
//  while (newz > 180) { newz -= 360.0; }
//  return newz;
//}

// If 
void shimmy() {
	dt.stop_all();
 
  float* data = ultron.read_dw_data();
  if (data[0] > DW_THRESH and data[2] > DW_THRESH) { // lf, rf
    Serial.println("BOTH FRONT");
    dt.back_slow();
    delay(SHIMMY_BACKUP);
    dt.turn_left();
  }
  else if (data[1] > DW_THRESH and data[3] > DW_THRESH) { // lb, rb 
    Serial.println("BOTH BACK");
    dt.forward_slow();
    delay(SHIMMY_BACKUP);
    dt.turn_left();
  }
  else if (data[0] > DW_THRESH) { // lf
    Serial.println("LEFT FRONT");
    dt.back_slow();
    delay(SHIMMY_BACKUP);
    dt.turn_right();
  } 
  else if (data[1] > DW_THRESH) { // lb
    Serial.println("LEFT BACK");
    dt.turn_right();
  }  
  else if (data[2] > DW_THRESH) { // rf
    Serial.println("RIGHT FRONT");
    dt.back_slow();
    delay(SHIMMY_BACKUP);
    dt.turn_left();
    
  }
  else if (data[3] > DW_THRESH) { // rb
    Serial.println("RIGHT BACK");
    dt.turn_left();
  }

  delete[] data; 

	dt.forward_slow();
}

void square_up(float orientation) {
  mpu6050.update();
  float z = mpu6050.getAngleZ();
  while (abs(z - orientation) > 3) {
    if (z > orientation) {
      dt.update_left(70);
      dt.update_right(-70);
    } else {
      dt.update_left(-70);
      dt.update_right(70);
    }
    delay(50);
    dt.stop_all();
    mpu6050.update();
    z = mpu6050.getAngleZ();
//    Serial.println(mpu6050.getAngleZ());
//    Serial.println(z);
//    Serial.println();
  }
  dt.stop_all();
}

void setup() {

  pixy.init();
  pixy.setLamp(0,0);
  pixy.changeProg("line_tracking");

  // dt.forward_slow();
  
  ultron.init(dw_pin_arr, ow_pin_arr);
  safety.init();
  Serial.begin(9600);
  //led.init();
  int8_t res;
  res = pixy.line.getMainFeatures();
  Serial.println(res);

  // init gyro
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}






int8_t backup_cnt = 0;
int8_t line_cnt = 0;
bool seen_hill = false;
float alpha = 0.1; 

void loop() {

  // If arming button is pressed, 
  // Release the lock and prepare to proceed

  if (digitalRead(ARM_BUTTON_PIN) == 0) {
    safety.arm_bot(); 
    for(int i = 0; i < 3; i++) {
      led_main.set_color(0, 1, 0);
      delay(ARM_DELAY/6);
      led_main.set_color(0, 0, 0);
      delay(ARM_DELAY/6);
    }
    
  };

  // Disable rest of loop if the safety conditions are not met
  if (safety.can_run() == false) {dt.stop_all(); return;}

  //dt.forward_slow();

  if (us_mode and !ultron.is_ow_safe()) {
    Serial.println("NOT SAFE");
    //led.set_color(1, 0, 0);
    // shimmy();
    //led.set_color(0, 0, 0);
  }

//  // Robot NOT SAFE. Need to recover
//	if (us_mode and !ultron.is_dw_safe()) {
//		Serial.println("NOT SAFE");
//    //led.set_color(1, 0, 0);
//		shimmy();
//    //led.set_color(0, 0, 0);
//	}
// 
//
//  // Robot SAFE. Drive normally
//  
//  // begin line following logic
//  if (lf_valid) {
//    int8_t res;
//    int32_t error; 
//    
//    // Get latest data from Pixy, including main vector, new intersections and new barcodes.
//    res = pixy.line.getMainFeatures();
//  
//    // if we're not line following, look for line
//    if (!lf_mode) {
//      if (res&LINE_VECTOR) {
//        if (line_cnt < LINE_CAP) {
//          line_cnt++;
//        } else {
//          lf_mode = true;
//          //led.set_color(0, 1, 0);
//          backup_cnt = 0;
//          line_cnt = 0;
//        }
//      }
//    } 
//    
//    // if we are line following, do line following
//    else {
//      // If NO LINE detected, backup
//      if (res<=0) 
//      {
//        dt.back_slow();
//        delay(80);
//        dt.stop_all();
//        Serial.print("stop ");
//        Serial.println(res);
//        backup_cnt++;
//        if (backup_cnt > BACKUP_CAP) {
//          lf_mode = false;
//          //led.set_color(0, 0, 0);
//          dt.forward_slow();
//        }
//      }
//    
//      // We found the vector...
//      else if (res&LINE_VECTOR)
//      {
//        backup_cnt = 0;
//        // Calculate heading error with respect to m_x1, which is the far-end of the vector,
//        // the part of the vector we're heading toward.
//        error = (int32_t)pixy.line.vectors->m_x1 - (int32_t)X_CENTER;
//        Serial.println("Error");
//        Serial.println(error);
//    
//        if (error > 5) {
//          dt.turn_right();
//        } else if (error < -5)
//        {
//          dt.turn_left();
//        } else {
//          dt.forward_slow();
//          delay(100);
//          dt.stop_all();
//        }
//      }
//    }
//  }
  
//  if (lf_mode and !ultron.is_ow_safe() and tictac_mode == false) {
//    lf_mode = false;
//    lf_valid = false;
//    us_mode = false;
//    tictac_mode = true;
//
//    led.set_color(0, 0, 1);
//    dt.stop_all();
//    square_up();
//    dt.forward_ludicrous();
//  }

  
}
