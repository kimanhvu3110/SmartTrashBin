#include "Servo_BIN.h"

Servo myservo_organic;
Servo myservo_inorganic;
void servo_init(){
	myservo_organic.attach(ORGANIC_BIN_PIN);
  myservo_inorganic.attach(INORGANIC_BIN_PIN);
}

void lift_the_bin_organic(){
	myservo_organic.write(180);
	delay(15);
}

void close_the_bin_organic(){
	myservo_organic.write(90);
	delay(15);
}

void lift_the_bin_inorganic(){
  myservo_inorganic.write(180);
  delay(15);
}

void close_the_bin_inorganic(){
  myservo_inorganic.write(0);
  delay(15);
}
