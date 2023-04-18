#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

#include "HC_SR.h" 
#include "Servo_BIN.h"

//Huu co
#define trigPin 2
#define echoPin 3 
//Vo co
#define trigPin2 4
#define echoPin2 5

SoftwareSerial espSerial(5, 6); //RX-TX 
//LiquidCrystal_I2C lcd(0x3F, 16, 2); // I2C address 0x27, 16 column and 2 rows
 
void setup() {
    // put your setup code here, to run once:
//    initHC_SR(); 
   
  //  lcd.init(); // initialize the lcd
  //  lcd.backlight();
    servo_init();
    Serial.begin(115200);
    espSerial.begin(115200);
    delay(2000);
}

void loop() {
    // put your main code here, to run repeatedly:
    //message = tempValue/lightValue/soilMoistureValue/tempCompare/lightCompare/soilMoistureCompare

    float level1 = trash_level(trigPin, echoPin);
    float level2 = trash_level(trigPin2, echoPin2);

    String message = String(level1) + " " + String(level2);
    Serial.println(message);
    lift_the_bin_inorganic();
    delay(2000);
    close_the_bin_inorganic();

    delay(1000);
//    String message = "";
//    String lcdMessage = "";
//    String lcdMessage2ndROW = "";
//    int soilMoistureValue = readMoisture();
//    float lightValue = checkLight();
//    float dhtValue = checkTemp();
//  
//    if (isnan(dhtValue)) {
//      message += "DHT is not connected";
//      lcdMessage += "Error";
//    }
//    else {
//      message += ("%d", dhtValue);
//      lcdMessage += String(dhtValue) + " C";
//    }
//    message += "/";
//    message += ("%f", lightValue);
//    message += "/";
//    message += ("%d", soilMoistureValue);
//  
//    lcdMessage += " ";
//    lcdMessage += ("%.0f", lightValue);
//    lcdMessage += " lux";
//  
//    lcdMessage2ndROW += String(soilMoistureValue);
//    lcdMessage2ndROW += "%";
//  
//    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print(lcdMessage);
//    lcd.setCursor(6, 1);
//    lcd.print(lcdMessage2ndROW);
//  
//    //message += ("40");
//    //message += "/";
//    //message += ("50");
//    //message += "/";
//    //message += ("100");
//   
//    Serial.println(message);
//    espSerial.println(message);
//    delay(3000);
}
