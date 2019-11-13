// Ultrasonic Sensor Publishing Example

#include <ros.h> 		// Include ROS
#include <std_msgs/String.h>	// Include String message type

ros::NodeHandle nh; 		// Create ROS node handler
std_msgs::String str_msg;  	// This is the string to send

// ROS publisher with name ultrasonic_vals and associated message
ros::Publisher string_pub("ultrasonic_vals", &str_msg); 

// Character array of message
char msg_str_in[30] = "Ultrasonic IN RANGE";
char msg_str_out[30] = "Ultrasonic OUT OF RANGE";

// Ultrasonic Sensor Connections
const int trig_pin = 9; 
const int echo_pin = 10; 

// Reading
bool prev_reading = false; 

void setup()
{

  pinMode(LED_BUILTIN, OUTPUT); 

  // Set up the ultrasonic sensor
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  // Initialise ROS
  nh.initNode();
  nh.advertise(string_pub);
  
  // 
  Serial.begin(57600);
}

void loop()
{
  // send signal
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW); 

  // listen for signal bounceback
  float dur = pulseIn(echo_pin, HIGH);
  
  // compute distance 
  float dist = dur*0.034/2;

  // Obtain the current "reading"
  // "True" if within range
  // "False" if out of range
  bool reading = prev_reading; 
  if (dist < 10) {reading = true; digitalWrite(LED_BUILTIN, 1);}
  else {reading = false;  digitalWrite(LED_BUILTIN, 0);}

  // Only publish anything if the signal has changed
  if (reading != prev_reading) {

    // Fill ROS message with data
    if (reading == true) {str_msg.data = msg_str_in;}
    else {str_msg.data = msg_str_out;}

    // Publish the message
    string_pub.publish( &str_msg );
    // Overwrite "previous" message
    prev_reading = reading; 
  } 

  // Update ROS callbacks etc. 
  nh.spinOnce();

}
