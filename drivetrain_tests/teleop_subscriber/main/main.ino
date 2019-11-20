
#include <ros.h>     // Include ROS
#include <std_msgs/Empty.h> // Include "Empty" message type
#include <std_msgs/Int16.h>

ros::NodeHandle nh; // Create ROS node handler

struct Motor {
  byte en;
  byte in1;
  byte in2;
};

Motor mA = {28, 30, 32}; // back left
Motor mB = {40, 42, 44}; // front left
Motor mC = {38, 34, 36}; // back right
Motor mD = {50, 46, 48}; // front right

Motor motors[4] = {mA, mB, mC, mD};

// drive individual wheels
void update_wheel(Motor mcur, int power) {
  if (power > 0) {
    digitalWrite(mcur.in1, HIGH);
    digitalWrite(mcur.in2, LOW);
  } else if (power < 0) {
    digitalWrite(mcur.in1, HIGH);
    digitalWrite(mcur.in2, LOW);
  } else {
    digitalWrite(mcur.in1, LOW);
    digitalWrite(mcur.in2, LOW);
  }
  analogWrite(mcur.en, power);
}

// drive left side of drive train
void update_left_cb(const std_msgs::Int16& power) {
  update_wheel(motors[0], power);
  update_wheel(motors[1], power);
}

// drive right side of drive train
void update_right_cb(const std_msgs::Int16& power) {
  update_wheel(motors[2], power);
  update_wheel(motors[3], power);
}

ros::Subscriber<std_msgs::Int16> sub_left("drive_left", &update_left_cb);
ros::Subscriber<std_msgs::Int16> sub_right("drive_right", &update_right_cb);

void setup()
{
  // set all the motor control pins to outputs
  for (int i=0; i< 4; i++) {
    Motor mcur = motors[i];
    pinMode(mcur.en, OUTPUT);
    pinMode(mcur.in1, OUTPUT);
    pinMode(mcur.in2, OUTPUT);
  }
  nh.initNode();
  nh.subscribe(sub1);
  nh.subscribe(sub2);
}

void loop() {
  nh.spinOnce(); 
}
