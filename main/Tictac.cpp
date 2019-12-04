
// Created by Rupesh Jeyaram and Iman Wahle
// Final Assignment -- ME 129
// Created 12/4/19

#include "Tictac.h"
#include "Arduino.h"

#include <Servo.h> // To control tic tac dropper

#define DISPENSER_PIN 6 // Pin for dispenser  

Servo dispenser;   // Servo object for dispenser

int location = 1510;

Tictac::Tictac()
{
  pinMode(DISPENSER_PIN, OUTPUT);
  dispenser.attach(DISPENSER_PIN);
  dispenser.write(location); 
}

void Tictac::drop_box() {
  dispenser.writeMicroseconds(1522);
  delay(2050);
  dispenser.writeMicroseconds(location);
}
