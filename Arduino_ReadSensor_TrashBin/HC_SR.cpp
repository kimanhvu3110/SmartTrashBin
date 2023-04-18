#include "HC_SR.h"
 
// defines variables
long duration;
float distance;
//long duration_2;
//float distance_2;
//void initHC_SR() {
//    pinMode(trigPin_2, OUTPUT); // Sets the trigPin as an Output
//    pinMode(echoPin_2, INPUT); // Sets the echoPin as an Input
//}

float trash_level(int trigPin, int echoPin) {
    //init
    
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
    // Clears the trigPin 
    digitalWrite(trigPin, LOW);
    delayMicroseconds(100); 
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2;
    // Prints the distance on the Serial Monitor
//    Serial.print("Distance: ");
//    Serial.println(distance);
    return distance;
    
} 
 
 
