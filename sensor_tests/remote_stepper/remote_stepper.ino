/* 
 * Remote-Control of Stepper Motor Test
 */

#include <ros.h> 		// Include ROS
#include <std_msgs/Int32.h>	// Include "Empty" message type

#include <Servo.h> // To control tic tac dropper

ros::NodeHandle nh; // Create ROS node handler

// const int stepsPerRevolution = 2038;  // change this to fit the number of steps per revolution

Servo dispenser; // Servo object for dispenser

#define DISPENSER_PIN 6 // Pin for dispenser  
int location = 1510;
bool started = false;  
// Stepper myStepper(stepsPerRevolution, 13, 12, 11, 10);

int stepCount = 0;  // number of steps the motor has taken

void messageCb( const std_msgs::Int32& loc_msg){
  dispenser.writeMicroseconds(1522);
  if (loc_msg.data == 0) {delay(2050);} else {delay(4000);}
  dispenser.writeMicroseconds(location);
}

ros::Subscriber<std_msgs::Int32> sub("drop", &messageCb );

void setup() { 
  pinMode(DISPENSER_PIN, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  dispenser.attach(DISPENSER_PIN);
  dispenser.write(location); 
}

void loop() {
  nh.spinOnce(); 
  delay(1);
}
