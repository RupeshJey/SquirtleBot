


//#include <SPI.h>
//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//

#include <Pixy2.h>
#include <PIDLoop.h>
// #include <ZumoMotors.h>
#include "MotorDriver.h"


// Zumo speeds, maximum allowed is 400
#define MOTOR_FAST        70
#define MOTOR_SLOW        -50
#define X_CENTER         (pixy.frameWidth/2)

Pixy2 pixy;
// ZumoMotors motors;
MotorDriver dt;

PIDLoop headingLoop(500, 50, 0, false);

int redPin = 33;
int greenPin = 37;
int bluePin = 35;

void setup() 
{
  
  Serial.begin(9600);
  Serial.print("Starting...\n");

  dt.init();
  pinMode(6, OUTPUT);
  dt.stop_all();

//  for (int i=0;i<1000;i++) {
//    dt.update_right(70);
//    dt.update_left(-(70));
//    //delay(300);
//    //dt.stop_all();
//    //delay(100);
//  }
//  delay(10000000);
//  dt.update_right(60);
//  delay(1000);
//  dt.update_right(-60);
//  delay(1000);
//  dt.update_right(0);
//  dt.update_left(60);
//  delay(1000);
//  dt.update_left(-60);
//  delay(1000);
//  dt.update_right(0);
//  dt.stop_all();
//  delay(5000);

  pixy.init();
  // Turn on both lamps, upper and lower for maximum exposure
  pixy.setLamp(0,0);
  // change to the line_tracking program.  Note, changeProg can use partial strings, so for example,
  // you can change to the line_tracking program by calling changeProg("line") instead of the whole
  // string changeProg("line_tracking")
  pixy.changeProg("line_tracking");

  pinMode(redPin, OUTPUT); 
  pinMode(greenPin, OUTPUT); 
  pinMode(bluePin, OUTPUT); 

}


void loop()
{
  int8_t res;
  int32_t error; 
  int left, right;
  char buf[96];

  // Get latest data from Pixy, including main vector, new intersections and new barcodes.
  res = pixy.line.getMainFeatures();

  // If error or nothing detected, stop motors
  if (res<=0) 
  {
    dt.stop_all();
    Serial.print("stop ");
    Serial.println(res);
    return;
  }

  // We found the vector...
  if (res&LINE_VECTOR)
  {
    // Calculate heading error with respect to m_x1, which is the far-end of the vector,
    // the part of the vector we're heading toward.
    error = (int32_t)pixy.line.vectors->m_x1 - (int32_t)X_CENTER;
    Serial.println("Error");
    Serial.println(error);

    if (error > 5) {
      dt.update_left(MOTOR_FAST);
      dt.update_right(MOTOR_SLOW);
    } else if (error < -5)
    {
      dt.update_left(MOTOR_SLOW);
      dt.update_right(MOTOR_FAST);
    } else {
      dt.update_left(60);
      dt.update_right(60);
    }
  }
  delay(200);
  dt.stop_all();
  delay(100);
  
//    Serial.println("Check this");
//    pixy.line.vectors->print();
//
//    // Perform PID calcs on heading error.
//    headingLoop.update(error);
//
//    // separate heading into left and right wheel velocities.
//    left = headingLoop.m_command;
//    right = -headingLoop.m_command;

//    
//    // If vector is heading away from us (arrow pointing up), things are normal.
//    if (pixy.line.vectors->m_y0 > pixy.line.vectors->m_y1)
//    {
//      // ... but slow down a little if intersection is present, so we don't miss it.
//      if (pixy.line.vectors->m_flags&LINE_FLAG_INTERSECTION_PRESENT)
//      {
//        left += MOTOR_SLOW;
//        right += MOTOR_SLOW;
//      }
//      else // otherwise, pedal to the metal!
//      {
//        left += MOTOR_FAST;
//        right += MOTOR_FAST;
//      }    
//    }
////    else  // If the vector is pointing down, or down-ish, we need to go backwards to follow.
////    {
//////      left -= MOTOR_SLOW;
//////      right -= MOTOR_SLOW;  
////    } 
//    Serial.println("PID Output");
//    Serial.println(headingLoop.m_command);
//    Serial.println("Left");
//    Serial.println(left);
//    Serial.println("Right");
//    Serial.println(right);
//
//    digitalWrite(greenPin, HIGH);
//    dt.update_left(left);
//    dt.update_right(right);
//  }
//
//  // If intersection, do nothing (we've already set the turn), but acknowledge with a beep.
//  if (res&LINE_INTERSECTION)
//  {
//    pixy.line.intersections->print();
//  }
//  //delay(1000);
}
