

#include "MotorDriver.h"
#include "Ultron.h"

Ultron ultron;
MotorDriver dt;

int dw_pin_arr[4][2] = {{28,29},{24,25},{10,11},{8,9}}; // lf, lb, rf, rb
int ow_pin_arr[4][2] = {{26,27},{22,23},{12,13},{40,41}};
// bool is_left[4] = {1,1,0,0};
// bool is_front[4] = {1,0,1,0};
int redPin = 33;
int greenPin = 37;
int bluePin = 35;
  
void shimmy() {
	dt.stop_all();
 
  float* data = ultron.read_dw_data();
  if (data[0] > DW_THRESH and data[2] > DW_THRESH) { // lf, rf
    Serial.println("BOTH FRONT");
    dt.back_slow();
    delay(500);
    dt.turn_180();
  }
  else if (data[1] > DW_THRESH and data[3] > DW_THRESH) { // lb, rb
    Serial.println("BOTH BACK");
    dt.forward_slow();
    delay(500);
    dt.turn_left();
  }
  else if (data[0] > DW_THRESH) { // lf
    Serial.println("LEFT FRONT");
    dt.back_slow();
    delay(500);
    dt.turn_right();
  } 
  else if (data[1] > DW_THRESH) { // lb
    Serial.println("LEFT BACK");
    dt.turn_right();
  }  
  else if (data[2] > DW_THRESH) { // rf
    Serial.println("RIGHT FRONT");
    dt.back_slow();
    delay(500);
    dt.turn_left();
  }
  else if (data[3] > DW_THRESH) { // rb
    Serial.println("RIGHT BACK");
    dt.turn_left();
  }

	dt.forward_slow();
}

void setup() {
  delay(3000);
  ultron.init(dw_pin_arr, ow_pin_arr);
	dt.forward_slow();
  Serial.begin(9600);

  pinMode(redPin, OUTPUT); 
  pinMode(greenPin, OUTPUT); 
  pinMode(bluePin, OUTPUT); 
}


int timer = 0;
void loop() {
  if (timer % 10000 == 0) {
//    float* data = ultron.read_dw_data();
//    for (int i = 0; i < 4; i++) {
//      Serial.println(data[i]);
//    }
  	if (!ultron.is_dw_safe()) {
  		Serial.println("NOT SAFE");
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, LOW);
      digitalWrite(redPin, LOW);
  		shimmy();
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, LOW);
      digitalWrite(redPin, LOW);
  	}
  }
  timer++;
}
