#ifndef wheels
#define wheels 

#define in1 30
#define in2 32
#define in3 34
#define in4 36
#define in5 42
#define in6 44
#define in7 46
#define in8 48
#define enA 28
#define enB 38
#define enC 40
#define enD 50

//Driving Funtions
void wheels_setup();
void stopAll(int delayTime); //stops the robot in place
void driveForward(int delayTime); //drives the robot forward
void driveBackward(int delayTime); //drives the robot backwards
void turnRight(int delayTime); //turns the robot to the right, delay time determines angle
void turnLeft(int delayTime); // turns robot to the left, delay time determines angle
void turnAround();

#endif
