// Created by Rupesh Jeyaram and Iman Wahle
// Final Assignment -- ME 129
// Created 11/15/19

#include "Ultrasonic.h"
#include "Ultron.h"

Ultron ultron;
void setup() {

    int pin_arr[4][2] = {{6,7},{5,4},{2,3},{8,9}};
    ultron.init(pin_arr);
    Serial.begin(9600);

}

void loop() {
    float* data = ultron.read_data();
    bool alert = false;
    for (int i=0; i<4; i++){
      if (data[i]>20) {
        alert = true;
      }
    }
    if (alert==true) {
      Serial.println("ALERTTTTT!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    } else{
        Serial.println("Safe");
    }

    //delay(1000); 

}
