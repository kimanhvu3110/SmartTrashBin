//Bấm * để submit ID
//Bấm # để delete char

#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(32,16,2);
int tempPin = A2; 
int val;
int temp;
char arrayID[10];

const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3}; 
byte colPins[COLS] = {4, 5, 6, 7}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
   
   lcd.begin(16,2);
   lcd.init();
   lcd.backlight();
  Serial.begin(9600);
  lcd.setCursor(2,0);
   lcd.print("Welcome !!!!");   
   delay(3000);
   lcd.clear();
   lcd.setCursor(1,0);
   lcd.print("Enter your ID:");
   }

void loop()
{
  char key = keypad.getKey(); 
  if(key){
    if(key == '#'){
      int i = 0;
      for(i = 0; i < 10; i++){
        Serial.print(arrayID[i]);
      }
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("The bin open");
    }
    else if (key == '*'){
      temp = 1;
      lcd.setCursor(val+1, 1);
      lcd.print(" ");
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
