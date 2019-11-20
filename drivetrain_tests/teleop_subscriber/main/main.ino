
#include <ros.h>     // Include ROS
#include <std_msgs/Empty.h> // Include "Empty" message type
#include <std_msgs/Int32MultiArray.h>

ros::NodeHandle nh; // Create ROS node handler

struct Motor {
  byte en;
  byte in1;
  byte in2;
};

Motor mA = {};
Motor mB = {};
Motor mC = {};
Motor mD = {};
int motors[] = [mA,mB,mC,mD];

ros::Subscriber<std_msgs::Empty> sub("drive", &drive_cb);

void setup()
{
  // set all the motor control pins to outputs
  for (int i=0; i< 4; i++) {
    mcur = motors[i];
    pinMode(mcur.en, OUTPUT);
    pinMode(mcur.in1, OUTPUT);
    pinMode(mcur.in2, OUTPUT);
  }
  nh.initNode();
  nh.subscribe(sub);
}

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

// drive right side of drive train
void update_right(int power) {
  update_wheel(mA, power);
  update_wheel(mB, power);
}

// drive left side of drive train
void update_left(int power) {
  update_wheel(mC, power);
  update_wheel(mD, power);
}

void drive_cb(const std_msgs::Int32MultiArray::ConstPtr& arr){
  update_right(arr[0]);
  update_left(arr[1]);
}

void loop() {
  nh.spinOnce(); 
}
