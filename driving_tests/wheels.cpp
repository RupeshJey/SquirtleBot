#include "wheels.h"
#include "Arduino.h"



void wheels_setup(){
  //Set up all the the pins
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enC, OUTPUT);
  pinMode(enD, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);
  //Enable pins to allow motion
  analogWrite(enA, 255); //Enable Motor A (F Right Motor)
  analogWrite(enB, 255); //Enable Motor B (B Right Motor)
  analogWrite(enC, 255); //Enable Motor C (F Left Motor)
  analogWrite(enD, 255); //Enable Motor D (B Left Motor)
}

void stopAll(int delayTime){
  //Stop all Wheels
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);
  //Hold time
  delay(delayTime);
}

void driveBackward(int delayTime){
  //Set Motor A forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  //Set Motor B forward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  //Set Motor C forward
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);
  //Set Motor D forward
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
  //Driving Time
  delay(delayTime);
}

void driveForward(int delayTime){
  //Set Motor A backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  //Set Motor B backward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  //Set Motor C backward
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  //Set Motor D backward
  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
  //Driving Time
  delay(delayTime);
}

void turnRight(int delayTime){
  //Set Motor A, B backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  //Set Motor C, D Forward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
  //Turning Time 
  delay(delayTime);
  stopAll(1);
}

void turnLeft(int delayTime){
  //Set Motor A, B Forward 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  //Set Motor C, D backward
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
  //Turning Time
  delay(delayTime);
  stopAll(1);
}

void turnAround(){
  turnRight(900);
}
