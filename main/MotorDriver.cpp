



#include "Arduino.h"
#include "MotorDriver.h"
Motor mA = {4, 36, 34}; // front left
Motor mB = {3, 30, 32}; // back left
Motor mC = {2, 44, 42}; // front right
Motor mD = {5, 46, 48}; // back right

Motor motors[4] = {mA, mB, mC, mD};


MotorDriver::MotorDriver() {

}

void MotorDriver::init() {
  //Set up all the the pins
  for (int i=0; i< 4; i++) {
    Motor mcur = motors[i];
    pinMode(mcur.en, OUTPUT);
    pinMode(mcur.in1, OUTPUT);
    pinMode(mcur.in2, OUTPUT);
    analogWrite(mcur.en, 255);
  }
}

// drive individual wheels
void MotorDriver::update_wheel(Motor mcur, int power) {
  if (power > 0) {
    digitalWrite(mcur.in1, HIGH);
    digitalWrite(mcur.in2, LOW);
  } else if (power < 0) {
    digitalWrite(mcur.in1, LOW);
    digitalWrite(mcur.in2, HIGH);
  } else {
    digitalWrite(mcur.in1, LOW);
    digitalWrite(mcur.in2, LOW);
  }
  analogWrite(mcur.en, abs(power));
}


// drive entire drive trainn
void MotorDriver::update_drive(int power) {
  update_wheel(motors[0], power);
  update_wheel(motors[1], power);   
  update_wheel(motors[2], power);
  update_wheel(motors[3], power); 
}

// drive entire drive trainn
void MotorDriver::update_left(int power) {
  update_wheel(motors[0], power);
  update_wheel(motors[1], power);   
}

// drive entire drive train
void MotorDriver::update_right(int power) {  
  update_wheel(motors[2], power);
  update_wheel(motors[3], power); 
}
void MotorDriver::stop_all(){
  update_drive(0);
}

void MotorDriver::turn_right() {
	update_left(SLOW);
	update_right(-1*SLOW);
  delay(TURN_DELAY);
  stop_all();
}

void MotorDriver::turn_left() {
	update_left(-1*SLOW);
	update_right(SLOW);
  delay(TURN_DELAY);
  stop_all();
}

void MotorDriver::turn_180() {
  update_left(-1*SLOW);
  update_right(SLOW);
  delay(TURN180_DELAY);
  stop_all();
}

void MotorDriver::forward_fast() {
  update_drive(FAST);
}

void MotorDriver::forward_slow() {
  update_drive(FAST);
  delay(BOOST_DELAY);
  update_drive(SLOW);
}

void MotorDriver::back_fast() {
  update_drive(-1*FAST);
}

void MotorDriver::back_slow() {
  update_drive(-1*FAST);
  delay(BOOST_DELAY);
  update_drive(-1*SLOW);
}
