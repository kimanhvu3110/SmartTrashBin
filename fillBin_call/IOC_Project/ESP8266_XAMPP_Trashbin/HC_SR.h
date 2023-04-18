#ifndef __HC_SR_H__
#define __HC_SR_H__

#include<Arduino.h>

//Huu co
#define trigPin D1
#define echoPin D2
//Vo co
#define trigPin2 D3
#define echoPin2 D4
 
//const int trigPin = 2;
//const int echoPin = 3; 
//const int trigPin_2 = 4;
//const int echoPin_2 = 5;

  
void initHC_SR();
float trash_level(int trigPin, int echoPin); 
 
#endif
