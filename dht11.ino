//#include <PID_v1.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Wire.h>
#include <Keypad.h>

float t=0;
int PWM_A = LOW; // moteur ventilateur
int PWM_B = LOW; // moteur fenetre
float temp_cons = 0;
float hysteresis = 2;
float temp_act = 0;
  /* ================= DEFINITION DU CLAVIER ========================= */
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
/* ========================= INITIALISATION DU LCD/KEYPAD ================== */ 
LiquidCrystal_I2C lcd(0x27,20,4);
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

/* ========================= DEFINITIONS DES PINs ========================= */

void setup() {
      //PID(RES_M, Adj_res, Value_reach,  );
     lcd.begin();
     pinMode(10, OUTPUT);
     lcd.backlight();
     lcd.setCursor(0,0);
     lcd.print("Temp : ");
     //Serial.begin(9600); 

}

/* ============================================================================ */

void loop() {

      DHT dht(2, DHT11);
      dht.begin();
      t = dht.readTemperature();
      float h = dht.readHumidity();
      char temp_min;
  /* ==================== AFFICHAGE TEMPERATURE DE CONSIGNE ========================== */
      if (temp_cons == NO_KEY ) {
          temp_cons = keypad.getKey();
          lcd.setCursor(3, 0);
          lcd.print(temp_cons);
       
      }
     char key = keypad.getKey();
      if (key == '#') {
            lcd.setCursor(1, 3);
            lcd.clear();
      
      }
   /* ================= HYSTERESIS: THermostat temperature =========================== */
      if (t <= temp_cons - hysteresis)  {
          
          digitalWrite(3, HIGH);
          digitalWrite(PWM_A , LOW);
          digitalWrite(PWM_B, LOW);
          lcd.setCursor(8, 3);
          lcd.print("heat ON ,Fan OFF");
      }
      if (t => temp_cons - hysteresis ) [
          digitalWrite(3, LOW);
          digitalWrite(PWM_A, HIGH);
          digitalWrite(PWM_B, HIGH);
          lcd.setCursor(8, 3);
          lcd.print("Heat OFF, Fan ON");
        
      }
   /* ======================GESTION DE L'ECRAN ======================================= */
   
      lcd.clear();
      lcd.print("Temp : ");
      lcd.print(t);
      lcd.setCursor(9, 0);
      lcd.print(" °C");
      lcd.setCursor(0, 1);
      lcd.print("Humidity :  ");
      lcd.setCursor(11, 1); 
      lcd.print(h);    
      Serial.println("Temperature: ");
      Serial.println(t);
      delay(2500);

}
