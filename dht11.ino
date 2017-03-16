//#include <PID_v1.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Wire.h>


float t=0;
int PWM_A = LOW; // moteur ventilateur
int PWM_B = LOW; // moteur fenetre
float temp_min = 0;
float temp_max = 0;
float Value_reach = 26;
LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {
      //PID(RES_M, Adj_res, Value_reach,  );
     lcd.begin();
     pinMode(3, OUTPUT);
     lcd.backlight();
     lcd.setCursor(0,0);
     lcd.print("Temp : ");
     //Serial.begin(9600); 

}
void loop() {

      DHT dht(2, DHT11);
      dht.begin();
      t = dht.readTemperature();
      float h = dht.readHumidity();
      if (t < temp_min)  {
          pinMode(3, HIGH);
          lcd.setCursor(8, 3);
          lcd.print("heat ON !!");
      }
      else {
          pinMode(3, LOW);
          pinMode(PWM_A, LOW);
          lcd.setCursor(8, 3);
          lcd.print("heat OFF !!");
        
      }
      if (t > temp_max) {

            pinMode(3, LOW);
            lcd.setCursor(8, 3);
            pinMode(PWM_A, HIGH);
            pinMode(PWM_B, HIGH);
      }
      lcd.clear();
      lcd.print("Temp : ");
      lcd.print(t);
      lcd.setCursor(9, 0);
      lcd.print(" C");
      lcd.setCursor(0, 1);
      lcd.print("Humidity :  ");
      lcd.setCursor(11, 1); 
      lcd.print(h);    
      Serial.println("Temperature: ");
      Serial.println(t);
      delay(2500);

}
