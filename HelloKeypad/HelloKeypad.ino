/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

LiquidCrystal_I2C lcd(0x27,20,4);
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  lcd.begin();
  lcd.setCursor(0,0);
  lcd.print("temp min :");
  lcd.setCursor(10,0);
}
  
void loop(){
  int key = keypad.getKey();
  if (key != NO_KEY){
    
    Serial.println(key);
    lcd.setCursor(10,0);
    lcd.print(key);
  }

  byte key2 = keypad.getKey();
  if (key2 != NO_KEY) {

      Serial.println(key2);
      lcd.setCursor(10,0);
      lcd.print(key2);
    
  }
  if (key == '#') {

      lcd.setCursor(10,0);
      lcd.clear();
      lcd.print("temp :");
  }
}
