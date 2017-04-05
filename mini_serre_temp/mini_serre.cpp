#include <Arduino.h>
#include <mini_serre.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h>
#define HYSTERESIS 2


void mini_serre::Menu(char key_menu)
{
  key_menu = keypad.getKey();
    while (key_menu == '#' ) {
          if (key_menu == '3' )
              break;
        key_menu = keypad.getKey();
        Serial.println(key_menu);

      //if (keypad.getState() == PRESSED && key == '#') {
        if (key_menu == '#' ) {

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("[1] :Temp Consigne");
        lcd.setCursor(0,1);
        lcd.print("[2] :Hum Consigne");
        lcd.setCursor(0,2);
        lcd.print("[3] :Exit ");
        delay(1000);
        }

    }

}

void Display(int temp_cons, int temp_dht, float h, bool StateRelay)
{
      lcd.clear();
      lcd.print("Temp : ");
      lcd.print(temp_dht);
      lcd.setCursor(9, 0);
      lcd.print(" set ");
      lcd.print(temp_cons);
      lcd.setCursor(0, 1);
      lcd.print("Humidity :  ");
      lcd.setCursor(11, 1);
      lcd.print(h);
  if (StateRelay == true) {

      lcd.print("Heat ON ,");
      lcd.print(" Fan OFF");

  }
  else {

      lcd.print("Heat OFF ,");
      lcd.print(" Fan ON");

  }
    lcd.setCursor(0,3);
    lcd.print("\'#\' to enter menu");
    delay(10);


}
bool Thermosat(int temp_cons, int temp_dht)
{
  int state = HIGH;
    if (temp_dht < temp_cons - HYSTERESIS)  {
        state = LOW;
    }
    digitalWrite(10, state);
    digitalWrite(PWM_A, state);
    digitalWrite(PWM_B, state);
    lcd.setCursor(2, 2);
    delay(1200);
    return (state == LOW ? true : false);

}
int ValueRead(int temp_cons, char key)
{
    int temp_cons = 0;
    int i = 0;
  while (i < 2) {
      char key = 0;
      key= keypad.getKey();
      if (key != NO_KEY) {
          if (key == '#')
              break;
          else if (key >= '0' && key <= '9') {
            i++;
            temp_cons = temp_cons * 10 + key - '0';
          }
      }
  }
    lcd.setCursor(0,3);
    lcd.print(temp_cons);
    delay(1200);
    return (temp_cons);


}
