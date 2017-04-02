//#include <PID_v1.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Wire.h>
#include <Keypad.h>

#define HYSTERESIS  2

int PWM_A = A1; // moteur ventilateur
int PWM_B = A2; // moteur fenetre

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
     lcd.init();
     pinMode(10, OUTPUT);
     digitalWrite(10, LOW);
     lcd.backlight();
     lcd.setCursor(0,0);
     lcd.print("Temp : ");
     Serial.begin(9600); 

}
 /* ==================== SAISIE TEMPERATURE DE CONSIGNE ========================== */
int  TempRead() {
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
   /* ================= HYSTERESIS: THermostat temperature =========================== */
  bool Thermostat(int temp_cons, int temp_dht) {    
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

/* ============================================================================ */
/* ======================GESTION DE L'ECRAN ======================================= */
void Display(int temp_cons, int temp_dht, float h, bool StateRelay) {

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
void Menu() {
    int key2 = keypad.getKey();
          if (key2 == '#') {
            Serial.println("asdasd");
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("[1] :Temp Consigne");
            lcd.setCursor(0,1);
            lcd.print("[2] :Hum Consigne");
            lcd.setCursor(0,2);
            lcd.print("[3] :Exit ");
                        delay(3000);

          }
}
void loop() {

      DHT dht(2, DHT11);
      dht.begin();
      Menu();
      int temp_dht = dht.readTemperature();
      float h = dht.readHumidity();
      int temp_cons = TempRead();
      bool StateRelay = Thermostat(temp_cons, temp_dht);
      Display(temp_cons, temp_dht, h, StateRelay);

}
