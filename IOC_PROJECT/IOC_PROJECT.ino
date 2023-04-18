#include <Wire.h>
#include <Servo.h>


#define LCD_address 0x3F
#define servo_pin 9
#define close_angle 90

//Open the trash bin with servo motor
void lift_the_bin(int pos) {
  Servo myservo;
  myservo.attach(servo_pin);
  myservo.write(pos);
}

//Close the trash bin with servo motor
void close_the_bin() {
  Servo myservo;
  myservo.attach(servo_pin);
  myservo.write(0);
}


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  lift_the_bin(close_angle);
  delay(100);
  close_the_bin();
}
