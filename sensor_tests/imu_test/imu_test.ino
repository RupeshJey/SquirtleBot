#include "Imu_Sensor.h"
#include "MotorDriver.h"
#include <Servo.h>

int redPin = 33;
int greenPin = 37;
int bluePin = 35;

float alpha = 0.1; 

float avg_incline = 0; 

bool upwards = false; 

MotorDriver dt;

Servo dispenser;
#define DISPENSER_PIN 6

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  Serial.println("Starting...");
  
  Serial.println("Done Starting...");

  dt.init();
  pinMode(6, OUTPUT);
  dt.stop_all();

  pinMode(redPin, OUTPUT); 
  pinMode(greenPin, OUTPUT); 
  pinMode(bluePin, OUTPUT); 
  
  dispenser.attach(DISPENSER_PIN);
  dispenser.write(1510);
}

void write_color(int r, int g, int b) {
  digitalWrite(redPin, r);
  digitalWrite(greenPin, g);
  digitalWrite(bluePin, b);
}

void loop() {

  int speed = 55 + avg_incline;
  //int uphill_speed = 90; 
  // put your main code here, to run repeatedly:
  Imu_Sensor imu;
  float incline = imu.get_fincline();
//  Serial.println(avg_incline);
  avg_incline = alpha * incline + (1 - alpha) * avg_incline; 
  if (avg_incline < 45) {
    write_color(1, 0, 0);

    dt.update_drive(speed);
    
    
    if (upwards == true) {

      Serial.println("Flat surface. Encountered ramp already. ");
      
      int k = 2000; 
    
      for (int i = 0; i < 2; i++) {
        dt.update_drive(speed);
        delay(200);
        dt.update_drive(0);
      
        dispenser.write(1530);
        if (i == 0) {
          delay(1000);
        }
        else {
          delay(k);
          k = k * 0.85;
        }
        dispenser.write(1510);
      }
      dt.stop_all();
      delay(1000000);
    }
    else {
      Serial.println("Flat surface. Haven't encountered ramp yet. ");
      dt.update_drive(speed);
    }
  }
  
  else {
    write_color(0, 1, 0);
    Serial.println("Ramp Surface");
    dt.update_drive(speed + avg_incline);
    upwards = true; 
  }
  delay(10);
}
