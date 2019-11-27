
// Created by Rupesh Jeyaram and Iman Wahle
// Final Assignment -- ME 129
// Created 11/24/19

 // #include <ros.h>     // Include ROS
 // #include <std_msgs/Empty.h> // Include "Empty" message type
 // #include <std_msgs/Int16.h>
 #include "Ultrasonic.h"
 #include "Ultron.h"

 // ros::NodeHandle nh; // Create ROS node handler
 Ultron ultron;      // Create Ultrasonic Handler
#include <Servo.h>

struct Motor {
  int en;
  int in1;
  int in2;
};

Motor mA = {3, 30, 32}; // back left
Motor mB = {2, 44, 42}; // front left
Motor mC = {4, 36, 34}; // back right
Motor mD = {5, 46, 48}; // front right

Motor motors[4] = {mA, mB, mC, mD};

int redPin = 33;
int greenPin = 37;
int bluePin = 35;

Servo dispenser;
#define DISPENSER_PIN 6

// drive individual wheels
void update_wheel(Motor mcur, int power) {
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
  analogWrite(mcur.en, power);
}

// drive entire drive trainn
void update_drive(int power) {
  update_wheel(motors[0], power);
  update_wheel(motors[1], power);   
  update_wheel(motors[2], power);
  update_wheel(motors[3], power); 
}

//// drive left side of drive train
//void update_left_cb(const std_msgs::Int16& power) {
//  update_wheel(motors[0], power.data);
//  update_wheel(motors[1], power.data); 
//}
//
//// drive right side of drive train
//void update_right_cb(const std_msgs::Int16& power) {
//
//  update_wheel(motors[2], int(power.data));
//  update_wheel(motors[3], int(power.data));
//}

// ros::Subscriber<std_msgs::Int16> sub_left("drive_left", &update_left_cb);
// ros::Subscriber<std_msgs::Int16> sub_right("drive_right", &update_right_cb);

void setup()
{
  Serial.begin(9600);
  // set all the motor control pins to outputs
  for (int i=0; i< 4; i++) {
    Motor mcur = motors[i];
    pinMode(mcur.en, OUTPUT);
    pinMode(mcur.in1, OUTPUT);
    pinMode(mcur.in2, OUTPUT);
    analogWrite(mcur.en, 255);
    pinMode(LED_BUILTIN, OUTPUT);

    pinMode(DISPENSER_PIN, OUTPUT);
    dispenser.attach(DISPENSER_PIN);
    dispenser.write(1510);
  }

//  // ultrasonic pins
//  pinMode(8, OUTPUT);
//  pinMode(9, INPUT);
//  pinMode(11, OUTPUT);
//  pinMode(10, INPUT);

  pinMode(redPin, OUTPUT); 
  pinMode(greenPin, OUTPUT); 
  pinMode(bluePin, OUTPUT); 
  
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, LOW);
  
  int speed = 50;
  update_drive(speed);


  // nh.initNode();
  // nh.getHardware()->setBaud(115200);
  // nh.subscribe(sub_left);
  // nh.subscribe(sub_right);
  
  int pin_arr[2][2] = {{8,9},{11,10}};
  ultron.init(pin_arr);
}

int timer = 0;
bool alert = false;
void loop() {

//  delay(10000);
//  digitalWrite(greenPin, HIGH);
//  digitalWrite(bluePin, LOW);
//  digitalWrite(redPin, LOW);

  // 1
  int speed = 55;
  int k = 2000; 

  for (int i = 0; i < 4; i++) {
    update_drive(speed);
    delay(500);
    update_drive(0);
  
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
  

  /// // 2

//  speed = 55;
//  update_wheel(motors[0], speed);
//  update_wheel(motors[1], speed);
//  update_wheel(motors[2], speed);
//  update_wheel(motors[3], speed);
//
//  delay(500);
//
//  speed = 0;
//  update_wheel(motors[0], speed);
//  update_wheel(motors[1], speed);
//  update_wheel(motors[2], speed);
//  update_wheel(motors[3], speed);
//
//  dispenser.write(1530);
//
//  delay(5000);
//
//  dispenser.write(1510);
//
//  //// 3
//
//  speed = 55;
//  update_wheel(motors[0], speed);
//  update_wheel(motors[1], speed);
//  update_wheel(motors[2], speed);
//  update_wheel(motors[3], speed);
//
//  delay(500);
//
//  speed = 0;
//  update_wheel(motors[0], speed);
//  update_wheel(motors[1], speed);
//  update_wheel(motors[2], speed);
//  update_wheel(motors[3], speed);
//
//  dispenser.write(1530);
//
//  delay(5000);
//
//  dispenser.write(1510);
//
//  //// 4
//
//  speed = 55;
//  update_wheel(motors[0], speed);
//  update_wheel(motors[1], speed);
//  update_wheel(motors[2], speed);
//  update_wheel(motors[3], speed);
//
//  delay(500);
//
//  speed = 0;
//  update_wheel(motors[0], speed);
//  update_wheel(motors[1], speed);
//  update_wheel(motors[2], speed);
//  update_wheel(motors[3], speed);
//
//  dispenser.write(1530);
//
//  delay(5000);
//
//  dispenser.write(1510);


  delay(1000000);

//  delay(1500);
//  speed = 45;
//  update_wheel(motors[0], -1*speed);
//  update_wheel(motors[1], -1*speed);
//  update_wheel(motors[2], speed);
//  update_wheel(motors[3], speed);
//  delay(1500);
//  speed = 0;
//  update_wheel(motors[0], speed);
//  update_wheel(motors[1], speed);
//  update_wheel(motors[2], speed);
//  update_wheel(motors[3], speed);
//  digitalWrite(greenPin, LOW);
//  digitalWrite(bluePin, HIGH);
//  digitalWrite(redPin, LOW);
//
//  delay(10000000);


//  float* data = ultron.read_data();
//  Serial.println(data[0]);
//  for (int i=0; i<2; i++){ 
//    if (data[i]>15) {
//      alert = true;
//    }
//  }
//  int speed = 0;
//  if (alert) {
//    Serial.println("ALLERT");
//    digitalWrite(greenPin, LOW);
//    digitalWrite(bluePin, LOW);
//    digitalWrite(redPin, HIGH);
//    update_drive(speed);
//  }
//  else if (timer > 10) {
//    speed = 35;
//    update_drive(speed);
//  }
//  timer = timer + 1;
//  delay(50);
  
  
  
  /*float* data = ultron.read_data();
  //Serial.println(data[0]);
  bool alert = false;
  for (int i=0; i<2; i++){ 
    if (data[i]>20) {
      alert = true;
    }
  }

  bool alert = false; 

  digitalWrite(8, LOW);
  delayMicroseconds(2);
  digitalWrite(8, HIGH);
  delayMicroseconds(10);
  digitalWrite(8, LOW);

  // listen for signal bounceback
  float dur1 = pulseIn(9, HIGH);
  float dist1 = dur1*0.034/2;

  digitalWrite(11, LOW);
  delayMicroseconds(2);
  digitalWrite(11, HIGH);
  delayMicroseconds(10);
  digitalWrite(11, LOW);

  // listen for signal bounceback
  float dur2 = pulseIn(10, HIGH);
  float dist2 = dur2*0.034/2;

   bool alert = true;
   if ((dist1 > 10 || dist2 > 10)==true) {

    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    digitalWrite(redPin, HIGH);
    
    digitalWrite(LED_BUILTIN,1);
    update_wheel(motors[0], 0);
    update_wheel(motors[1], 0);
    update_wheel(motors[2], 0);
    update_wheel(motors[3], 0);
  }
  else {
    digitalWrite(LED_BUILTIN,0);
    
      if (timer > 50) {
        int speed = 40;
        
        digitalWrite(greenPin, HIGH);
        digitalWrite(bluePin, HIGH);
        digitalWrite(redPin, LOW);
        update_wheel(motors[0], speed);
        update_wheel(motors[1], speed);
        update_wheel(motors[2], speed);
        update_wheel(motors[3], speed);
      }*/
    /*update_wheel(motors[0], 55);
    update_wheel(motors[1], 55);
    update_wheel(motors[2], 55);
    update_wheel(motors[3], 55);
  }

   nh.spinOnce();
  delay(20);
  timer = timer + 1;
  */
}
