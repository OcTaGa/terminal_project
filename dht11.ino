//#include <PID_v1.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Wire.h>
#include <Keypad.h>

float t=0;
int PWM_A = A1; // moteur ventilateur
int PWM_B = A2; // moteur fenetre

float hysteresis = 2;
float temp_act = 0;
char temp_read[2]={0,0};
int temp_cons;
  /* ================= DEFINITION DU CLAVIER ========================= */
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS]  = {
      {'1','2','3'},
      {'4','5','6'},
      {'7','8','9'},
      {'*','0','#'}
};
byte rowPins[ROWS] = {4, 5, 6, 7};
byte colPins[COLS] = {8, 9, 10};
/* ========================= INITIALISATION DU LCD/KEYPAD ================== */ 
LiquidCrystal_I2C lcd(0x27,20,4);
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

/* ========================= DEFINITIONS DES PINs ========================= */

void setup() {
      //PID(RES_M, Adj_res, Value_reach,  );
     lcd.begin();
     pinMode(3, OUTPUT);
     lcd.backlight();
     lcd.setCursor(0,0);
     lcd.print("Temp : ");
     Serial.begin(9600); 

}
 /* ==================== SAISIE TEMPERATURE DE CONSIGNE ========================== */
void TempRead() {
 
    int i = 0;
     while (i < 2) {
char key = 0;
      key= keypad.getKey();
        if (key != NO_KEY) {
          //if (key == '#') break;
       temp_read[i] = key;
       i++;
        }
        else {
              Serial.println(key);
              lcd.print(key);
          
        }
        int temp_cons = (temp_read[0]-'0')*10 + (temp_read[1]-'0');
   lcd.setCursor(0,3);


  }
  Serial.println(temp_cons);
  lcd.print(temp_cons);
}

  void Thermostat() {    
      
      if (t <= temp_cons - hysteresis)  {
          
          digitalWrite(3, HIGH);
          digitalWrite(PWM_A , LOW);
          digitalWrite(PWM_B, LOW);
          lcd.setCursor(8, 2);
          lcd.print("heat ON ,Fan OFF");
      }
      if (t >= temp_cons - hysteresis ) {
          digitalWrite(3, LOW);
          digitalWrite(PWM_A, HIGH);
          digitalWrite(PWM_B, HIGH);
          lcd.setCursor(8, 2);
          lcd.print("Heat OFF, Fan ON");
        
      }

  }

/* ============================================================================ */

void loop() {

      DHT dht(2, DHT11);
      dht.begin();
      t = dht.readTemperature();
      float h = dht.readHumidity();
      char temp_min;
      TempRead();
      Thermostat();
     
      
   /* ================= HYSTERESIS: THermostat temperature =========================== */

   /* ======================GESTION DE L'ECRAN ======================================= */
   
      lcd.clear();
      lcd.print("Temp : ");
      lcd.print(t);
      lcd.setCursor(9, 0);
      lcd.print(" C");
      lcd.setCursor(0, 1);
      lcd.print("Humidity :  ");
      lcd.setCursor(11, 1); 
      lcd.print(h);
      
      //Serial.println("Temperature: ");
      //Serial.println(t);
      delay(10);

}
