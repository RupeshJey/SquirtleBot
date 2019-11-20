/* 
 * Remote-Control of Stepper Motor Test
 */

#include <ros.h> 		// Include ROS
#include <std_msgs/Empty.h>	// Include "Empty" message type

#include <Stepper.h> 		// Include stepper motor library

ros::NodeHandle nh; // Create ROS node handler

const int stepsPerRevolution = 2038;  // change this to fit the number of steps per revolution
Stepper myStepper(stepsPerRevolution, 13, 12, 11, 10);

int stepCount = 0;  // number of steps the motor has taken

void messageCb( const std_msgs::Empty& toggle_msg){
  myStepper.setSpeed(10);
  myStepper.step(510);
}

ros::Subscriber<std_msgs::Empty> sub("drop", &messageCb );

void setup() { 
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce(); 
  delay(1);
}
