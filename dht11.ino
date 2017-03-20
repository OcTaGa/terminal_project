//#include <PID_v1.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Wire.h>
#include <Keypad.h>

float t=0;
int PWM_A = LOW; // moteur ventilateur
int PWM_B = LOW; // moteur fenetre
float temp_act = 0;

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS]  = {
      {'1','2','3'},
      {'4','5','6'},
      {'7','8','9'},
      {'*','0','#'}
};
byte rowPins[ROWS] = {6, 5, 4, 3};
byte colPins[COLS] = {9, 8, 7};

LiquidCrystal_I2C lcd(0x27,20,4);
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
      //PID(RES_M, Adj_res, Value_reach,  );
     lcd.begin();
     pinMode(10, OUTPUT);
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
      char temp_min;
      if (temp_min = NO_KEY) {
          temp_min = keypad.getKey();
          lcd.setCursor(1,3);
          lcd.print(temp_min);
      }
      char key = keypad.getKey();
      if (key == '#') {
            lcd.setCursor(1, 3);
            lcd.clear();
      
      }

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
    /*  if (t > temp_max) {

            pinMode(3, LOW);
            lcd.setCursor(8, 3);
            pinMode(PWM_A, HIGH);
            pinMode(PWM_B, HIGH);
      } */
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
