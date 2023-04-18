#ifndef __Servo_BIN__
#define __Servo_BIN______

#include<Arduino.h>
#include <Servo.h>

#define ORGANIC_BIN_PIN 5
#define INORGANIC_BIN_PIN 4

void servo_init();
void lift_the_bin_organic();
void close_the_bin_organic();
void lift_the_bin_inorganic();
void close_the_bin_inorganic();

 
#endif
