
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Wire.h>
#include <Keypad.h>
#define HYSTERESIS  2

int PWM_A = A1; // moteur fenetre
int PWM_B = A2; // moteur fenetre
char key_menu = NO_KEY ;
int value_cons = 20;
int temp_cons = 50;
int Hum_Value = 0;
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

/*===========================INITIALISATION CAPTEUR=======================*/

DHT dht(2, DHT11);

/* ========================= INITIALISATION DU LCD/KEYPAD ================== */ 

LiquidCrystal_I2C lcd(0x27,20,4);
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


/* ========================= DEFINITIONS DES PINs ========================= */

void setup() {

     dht.begin();
     lcd.init();
     pinMode(10, OUTPUT);
     digitalWrite(10, LOW);
     lcd.backlight();
     lcd.setCursor(0,0);
     lcd.print("Temp : ");
     Serial.begin (9600);


}
 


/*=============================BOUCLE PRINCIPALE=====================================*/

void loop() {

          key_menu = keypad.getKey();
          delay(50);
          Serial.println(key_menu);
      if (key_menu == '#') { 
              Menu();
      }
          int temp_dht = dht.readTemperature();
          float h = dht.readHumidity();
          bool StateRelay_1 = Thermostat(temp_cons, temp_dht);
          bool StateRelay_2 = ThermostatHum(Hum_cons, Hum_Value );
          Display(temp_cons, temp_dht, h, StateRelay);

delay (100);
}


/* ==================== FONCTION SAISIE TEMPERATURE DE CONSIGNE ========================== */
 
int  ValueRead() {
    value_cons = 0;
    int i = 0;
    while (i < 2) {
        char key = 0;
        key= keypad.getKey();
        delay(10);
        if (key != NO_KEY) {
            if (key == '#')
                break;
            else if (key >= '0' && key <= '9') {
              i++;
              value_cons = value_cons * 10 + key - '0';
            }
        }
    }
  lcd.clear();
    return (value_cons);
}

 
   /* ================= FONCTION REGULATION TEMPERATURE =========================== */
   
  bool Thermostat(int temp_cons, int temp_dht) {    
      int state_A = HIGH;
      if (temp_dht < temp_cons - HYSTERESIS)  {
          state = LOW;
      }
      digitalWrite(10, state_A);
      digitalWrite(PWM_A, state_A);
      digitalWrite(PWM_B, state_A);
      lcd.setCursor(2, 2);
      return (state_A == LOW ? true : false);
  }

bool ThermostatHum(int Hum_cons, int Hum_Value) {
  
    int State_B = HIGH;
    if (Hum_Value < Hum_cons - HYSTERESIS) {
         State_B = LOW;  
  
    }
      analogWrite(, State_B); // Brumisateur
      digitalWrite(, State_B); // moteur fenêtre
      digitalWrite(, State_B); // moteur fenêtre 

}
/* ======================GESTION DE L'ECRAN ======================================= */
void Display(int temp_cons, int temp_dht, float h, bool StateRelay_1, bool Staterelay_2) {

      //lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Temp : ");
      lcd.print(temp_dht);
      lcd.setCursor(12, 0);
      lcd.print("set:");
      lcd.print(temp_cons);
      lcd.setCursor(0, 1);
      lcd.print("H% :  ");
      lcd.setCursor(5, 1); 
      lcd.print(h);
      lcd.setCursor(0,2);
      if (StateRelay_1 == true) {

          lcd.print("Heat OFF ,"); // remplacer ces lignes par allumage de LED ( GREEN=Allumer et RED=Eteint )
          lcd.print(" Fan ON");    // ********
        
      }
      else {

          lcd.print("Heat ON ,"); //de même ici 
          lcd.print(" Fan OFF ");  //*******
        
      }
      lcd.setCursor(0,3);
      lcd.print("\'#\' to enter menu");

  
}
/*====================== FONCTION HUMREAD ===========================================*/
Hum
      



/*====================== FONCTION  GESTION DES MENUS====================================*/

  void Menu() {
                Serial.println( "menu");
               lcd.clear();
               lcd.setCursor(0,0);
               lcd.print("[1] :Set Temperature");
               lcd.setCursor(0,1);
               lcd.print("[2] :Set RH%");
               lcd.setCursor(0,2);
               lcd.print("[3] :Exit ");
               int key_menu = 0;
               
               while (key_menu != 51){
          
                int key_menu = keypad.getKey();
                delay (100);
                if (key_menu != NO_KEY){
                //Serial.println(key_menu);
        switch ( key_menu ) {
              
              case 49: {
                  lcd.clear();
                  
                  lcd.print("Temp consigne : ");
                  int temp_cons = ValueRead();
                  lcd.print(temp_cons);
                  break;
              }
              case 50: {
              
                  lcd.clear();
                  
                  lcd.print("RH% consigne : ");
                  int hum_cons= ValueRead();
                  lcd.print(temp_cons);
                  break;
              }
              case 51: {
                
                  lcd.print("Luminosity :");
                  int Lum_hours = ValueRead();
                  lcd.print(temp_cons);
                  break;   
              }
              case 52: {

                     lcd.clear();
                break;
              }

               break;

        }

        break;
        }
       
      }
    }

     
