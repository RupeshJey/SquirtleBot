
#include <ros.h>     // Include ROS
#include <std_msgs/Empty.h> // Include "Empty" message type
#include <std_msgs/Int16.h>

ros::NodeHandle nh; // Create ROS node handler

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

// drive left side of drive train
void update_left_cb(const std_msgs::Int16& power) {
  digitalWrite(LED_BUILTIN,1);
  delay(power.data * 10);
  digitalWrite(LED_BUILTIN,0);
  update_wheel(motors[0], power.data);
  update_wheel(motors[1], power.data); 
  update_wheel(motors[2], power.data);
  update_wheel(motors[3], power.data);
  delay(2000);
  update_wheel(motors[0], 0);
  update_wheel(motors[1], 0);
  update_wheel(motors[2], 0);
  update_wheel(motors[3], 0);
}

// drive right side of drive train
void update_right_cb(const std_msgs::Int16& power) {

  update_wheel(motors[2], int(power.data));
  update_wheel(motors[3], int(power.data));
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
    analogWrite(mcur.en, 255);
    pinMode(LED_BUILTIN, OUTPUT);

    digitalWrite(LED_BUILTIN,1);
    delay(500);
    digitalWrite(LED_BUILTIN,0);
    delay(500);
    digitalWrite(LED_BUILTIN,1);
    delay(500);
    digitalWrite(LED_BUILTIN,0);
    delay(500);
    digitalWrite(LED_BUILTIN,1);
    delay(500);
    digitalWrite(LED_BUILTIN,0);
    
  }
  nh.initNode();
  nh.subscribe(sub_left);
  nh.subscribe(sub_right);
}

void loop() {
  nh.spinOnce(); 
}
