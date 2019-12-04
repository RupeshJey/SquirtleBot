
#include <Pixy2.h>
#include <PIDLoop.h>

#include "MotorDriver.h"
#include "Ultron.h"
#include "LED.h"

#define ARM_BUTTON_PIN 45


Ultron ultron;
MotorDriver dt;
LED led; 
Pixy2 pixy;

#define X_CENTER         (pixy.frameWidth/2)

int dw_pin_arr[4][2] = {{28,29},{24,25},{10,11},{8,9}}; // lf, lb, rf, rb
int ow_pin_arr[4][2] = {{26,27},{22,23},{12,13},{40,41}};
// bool is_left[4] = {1,1,0,0};
// bool is_front[4] = {1,0,1,0};
  
void shimmy() {
	dt.stop_all();
 
  float* data = ultron.read_dw_data();
  if (data[0] > DW_THRESH and data[2] > DW_THRESH) { // lf, rf
    Serial.println("BOTH FRONT");
    dt.back_slow();
    delay(500);
    dt.turn_180();
  }
  else if (data[1] > DW_THRESH and data[3] > DW_THRESH) { // lb, rb
    Serial.println("BOTH BACK");
    dt.forward_slow();
    delay(500);
    dt.turn_left();
  }
  else if (data[0] > DW_THRESH) { // lf
    Serial.println("LEFT FRONT");
    dt.back_slow();
    delay(500);
    dt.turn_right();
  } 
  else if (data[1] > DW_THRESH) { // lb
    Serial.println("LEFT BACK");
    dt.turn_right();
  }  
  else if (data[2] > DW_THRESH) { // rf
    Serial.println("RIGHT FRONT");
    dt.back_slow();
    delay(500);
    dt.turn_left();
  }
  else if (data[3] > DW_THRESH) { // rb
    Serial.println("RIGHT BACK");
    dt.turn_left();
  }

  delete[] data; 

	dt.forward_slow();
}

void setup() {

  pixy.init();
  pixy.setLamp(0,0);
  pixy.changeProg("line_tracking");
  
  delay(3000);

  dt.forward_slow();
  
  ultron.init(dw_pin_arr, ow_pin_arr);
  Serial.begin(9600);
  led.init();
  int8_t res;
  res = pixy.line.getMainFeatures();
  Serial.println(res);
}


uint16_t timer = 0;

void loop() {

  //Serial.println(timer);

//  timer++;
//  
//  if (timer >= 10000) {
//    // Robot NOT SAFE. Need to recover
//  	if (!ultron.is_dw_safe()) {
//  		Serial.println("NOT SAFE");
//      led.set_color(1, 0, 0);
//  		shimmy();
//      led.set_color(0, 0, 0);
//  	}
//    timer = 0; 
//  }
  

  

  // Robot SAFE. Drive normally

  // Look for line

  int8_t res;
  int32_t error; 

  // Get latest data from Pixy, including main vector, new intersections and new barcodes.
  res = pixy.line.getMainFeatures();

  // If NO LINE detected
  // If error or nothing detected, stop motors
  if (res<=0) 
  {
    dt.back_slow();
    delay(50);
    dt.stop_all();
    Serial.print("stop ");
    Serial.println(res);
  }

  // We found the vector...
  else if (res&LINE_VECTOR)
  {
    // Calculate heading error with respect to m_x1, which is the far-end of the vector,
    // the part of the vector we're heading toward.
    error = (int32_t)pixy.line.vectors->m_x1 - (int32_t)X_CENTER;
    Serial.println("Error");
    Serial.println(error);

    if (error > 5) {
      dt.turn_right();
    } else if (error < -5)
    {
      dt.turn_left();
    } else {
      dt.forward_slow();
      delay(100);
      dt.stop_all();
    }
  }
      
  //dt.stop_all();
  //delay(100);
}
