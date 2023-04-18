#ifndef __HC_SR_H__
#define __HC_SR_H__

#include<Arduino.h>
 
//const int trigPin = 2;
//const int echoPin = 3; 
//const int trigPin_2 = 4;
//const int echoPin_2 = 5;

  
void initHC_SR();
float trash_level(int trigPin, int echoPin); 
 
#endif
