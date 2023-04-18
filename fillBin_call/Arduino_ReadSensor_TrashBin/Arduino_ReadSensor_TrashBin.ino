//#include "Keypad.h" 
//#include "LoadCell.h" 
#include "Servo.h" 
#include "HX711.h"  
#include <SoftwareSerial.h> 
SoftwareSerial espSerial(5, 6); //RX-TX  

///////////////////////////////////////
#include <Keypad.h>
#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
 
int tempPin = A2; 
int val;
int temp;
int tempn;
char arrayID[10];
String message;

const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {6, 7, 8, 9}; 
byte colPins[COLS] = {10, 11, 12, 13}; 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//////////////////////

HX711 scale;
#define DOUT 2
#define CLK 3
#define calibration_factor 71500 
/////////////////////////////////////// 
void setup() {
    //1. Init 
    Serial.begin(115200); 
    init_keyPad(); 
//    Serial.print("init_keyPad() done");
//    init_LoadCell();
//    Serial.print("init_LoadCell() done");
    
    //Hx711 init
    scale.begin(DOUT, CLK);
    scale.set_scale();
    
    long zero_factor = scale.read_average(); //đọc thông tin  
//    Serial.print("Zero factor: "); 
//    Serial.println(zero_factor);

    servo_init();
//    Serial.println("servo_init() done"); 
    
    espSerial.begin(115200);
//    Serial.println("ran here");
    
} 
////////////////////////////////////////////////////////////////////////////
 
  
float LoadCell() {
    scale.set_scale(calibration_factor); //điều chỉnh theo hệ số hiệu chỉnh
//    Serial.print(" calibration_factor: ");Serial.print(calibration_factor);  
    float weight;   
    for(int i=0; i<20; i++){  
//        Serial.print("Reading: ");Serial.print(scale.get_units(), 3);  
        weight = scale.get_units(3);
//        Serial.print("Weight: ");Serial.print(weight);Serial.println(" KG"); 
        delay(100); 
    }
    return weight;
} 
 
void init_keyPad(){
    lcd.begin(16,2);
    lcd.init();
    lcd.backlight(); 
    lcd.setCursor(2,0);
    lcd.print("Welcome !!!!");   
    delay(1000);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Enter your ID:");
}
 
void keyPad(){ //return ID
    char key = keypad.getKey();  
    if(key){
        //Case1:#
        if(key == '#'){
            temp = 2;
            int i = 0;
            for(i = 0; i < 10; i++){
               message += arrayID[i];
                //Serial.print(arrayID[i]);
            }
            lcd.clear();
            lcd.setCursor(2, 0);
            //Open bin
            lcd.print("The bin open");
            delay(1000);
            //open trash
            lift_the_bin_organic();
            lift_the_bin_inorganic();
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("It's organic?");
            lcd.setCursor(0,1);
            lcd.print("B:Yes  C:No");             
        }
        //Case2:*
        else if (key == '*'){
            temp = 1;
            lcd.setCursor(val+1, 1);
            lcd.print(" ");
        }
        //Case3:*
        else if (key == 'A'){
            lcd.setCursor(2,0);
            lcd.print("Welcome !!!!");   
            delay(2000);
            lcd.clear();
            lcd.setCursor(1,0);
            lcd.print("Enter your ID:");
            val = 0;
            temp = 0;
        }
        else if(key == 'B'){
          if(temp == 2){
           // Serial.print("/1");
            tempn = 1;
            scale.tare(); //Reset giá trị về 0
            delay(500);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Put organic");
            delay(500);
            
            //LoadCell
            float weight = LoadCell();
            
            lcd.setCursor(0,1);
            lcd.print(weight);
            lcd.print("kg");
            message += ("/");
            message += weight;
            //Serial.print("/");
            //Serial.print(weight);            
            delay(3000);
            temp = 3;
            lcd.clear();
            lcd.print("Next nonorgan");
            lcd.setCursor(0,1);
            lcd.print("B:Yes  C:No"); 
            delay(3000);
            
          }else if(temp == 3){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Put nonorganic");
            //Serial.print("/2");
            tempn = 1;
            scale.tare(); //Reset giá trị về 0
            delay(500);
            
            //LoadCell
            float weight = LoadCell();
            lcd.setCursor(0,1);
            lcd.print(weight);
            lcd.print("kg");
            message += ("/");
            message += weight;
            //Serial.print("/");
            //Serial.print(weight);
            
            delay(3000);
            close_the_bin_organic();
            close_the_bin_inorganic();
            lcd.clear();
            lcd.print("Thank you");
            //Serial.println();
            temp = 4;
          }
        }
        
        else if(key == 'C'){
          tempn = 2;
          if(temp == 2){
            //Serial.print("/1");
            //Serial.print("/0");
            message += ("/0");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Put nonorganic");
            //Serial.print("/2");
            tempn = 1;
            scale.tare(); //Reset giá trị về 0
            delay(1000);
            
            //LoadCell
            float weight = LoadCell();
            lcd.setCursor(0,1);
            lcd.print(weight);
            lcd.print("kg");
            message += ("/");
            message += weight;
            //Serial.print("/");
            //Serial.print(weight);
            
            delay(3000);
            close_the_bin_organic();
            close_the_bin_inorganic();
            lcd.clear();
            lcd.print("Thank you");
            //Serial.println();   
            temp = 4;
                    
          }else if(temp == 3){
            //Serial.print("/0");
            message += ("/0");
            delay(500);
            lcd.clear();
            lcd.print("Thank you");
            close_the_bin_organic();
            close_the_bin_inorganic();
            temp = 4;
          }
        }        
        else{
            if(temp == 1){
                arrayID[val-1] = key;
                lcd.setCursor(val+1, 1);
                lcd.print(arrayID[val-1]);
                temp = 0;
            }
            else{
                arrayID[val] = key;
                lcd.setCursor(val+2, 1);
                lcd.print(arrayID[val]);
                val = val + 1;
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////
void loop() { 
    //message = HCSR_ID/HCSR_value/soilMoistureValue/tempCompare/lightCompare/soilMoistureCompare

    //1. Init
//    String message = "";

    //2.Read value 
    
    //Serial.print("here");
    keyPad();
    if(temp == 4){
      Serial.println(message);
      espSerial.println(message);
      message = "";
      temp = 0;
    }


    delay(1000);
}
