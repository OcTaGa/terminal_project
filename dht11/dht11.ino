
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Wire.h>
#include <Keypad.h>
#define HYSTERESIS  2

int PWM_A = A1; // moteur fenetre
int PWM_B = A2; // moteur fenetre
char key_menu = NO_KEY ;
int temp_cons = 20;
int sensorPin = A0;
int hum_dht = 50;
int Hum_Ground = 0;
int Hum_cons = 50;
bool StateRelay_2 ;
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
     pinMode(11, OUTPUT);
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
      if (key_menu == '#') { 
              Menu();
      }
          int temp_dht = dht.readTemperature();
          int hum_dht = dht.readHumidity();
          bool StateRelay_1 = Thermostat(temp_cons, temp_dht);
          bool StateRelay_2 = ThermostatHum(Hum_cons, hum_dht );
          Display(temp_cons, temp_dht, hum_dht, StateRelay_1, StateRelay_2, Hum_cons);
Serial.println (temp_cons);
delay (100);
}


/* ==================== FONCTION SAISIE TEMPERATURE DE CONSIGNE ========================== */
 
int  ValueRead() {
    int value_cons = 0;
    int i = 0;
    while (i < 2) {
        char key = 0;
        key= keypad.getKey();
        delay(50);
        if (key != NO_KEY) {
            if (key == '#')
                break;
            else if (key >= 48 && key <= 57) {
              i++;
              value_cons = value_cons * 10 + key - 48;
            }
        }
    }
        lcd.clear();
        //Serial.println(value_cons);
    return (value_cons);
}

 
   /* ================= FONCTION REGULATION TEMPERATURE =========================== */
   
  bool Thermostat(int temp_cons, int temp_dht) {    
      bool state_A = HIGH;
      bool state_B = HIGH;
      if (temp_dht < temp_cons - HYSTERESIS)  {
          state_A = LOW;
          state_B = HIGH;
      }
      else {
          state_A = HIGH;
          state_B = LOW;
      }
      digitalWrite(11, state_A);           //commande relai chauffage
      //digitalWrite(PWM_A, state_A);      //commande moteur ouverture et fermeture
      //digitalWrite(PWM_B, state_A);
      digitalWrite(10, state_B);          //commande relai ventillateur
      
      lcd.setCursor(2, 2);
      return (state_A == LOW ? true : false);
  }

bool ThermostatHum(int Hum_cons, int hum_dht) {
  
    int State_B = HIGH;
    if (hum_dht < Hum_cons - HYSTERESIS) {
         State_B = LOW;  
  
    }
      //analogWrite(11, State_B); // resistance chauffage
     // digitalWrite(, State_B); // moteur fenêtre
     // digitalWrite(, State_B); // moteur fenêtre 
     // Penser à mettre des LED pour check ce qui est allumer.
    return (State_B == LOW ? true : false);
}
/* ======================GESTION DE L'ECRAN ======================================= */
void Display(int temp_cons, int temp_dht, int hum_dht, bool StateRelay_1, bool Staterelay_2, int Hum_cons) {

      //lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Temp : ");
      lcd.print(temp_dht);
      lcd.print("-C");      // /!\ ACCEPTE LES CODE ASCII DANS CETTE ORTHOGRAPHES ?????
      lcd.setCursor(12, 0);
      lcd.print("set: ");
      lcd.print(temp_cons);
      lcd.setCursor(0, 1);
      lcd.print("H% :  ");
      lcd.setCursor(5, 1); 
      lcd.print(hum_dht);
      lcd.setCursor(12,1);
      lcd.print("set: ");
      lcd.print(Hum_cons);
      lcd.setCursor(0,2);
      if (StateRelay_1 == true) {

          lcd.print("Heat ON ,"); // remplacer ces lignes par allumage de LED ( GREEN=Allumer et RED=Eteint )
          lcd.print(" Fan OFF");    // ********
        
      }
      else {

          lcd.print("Heat OFF ,"); //de même ici 
          lcd.print(" Fan ON ");  //*******
        
      }
      if (StateRelay_2 == true) {
        
             digitalWrite(12, HIGH);
           //  digitalWrite(11// Allumer led verte et éteindre led Rouge
        
      }
      else {
        
              // Eteindre Led Verte et allumer Led rouges correspondante. 
        
      }
      lcd.setCursor(0,3);
      lcd.print("\'#\' to enter menu");
      
}
/*====================== FONCTION HUMREAD ===========================================*/
int HumRead(int Hum_Ground, int sensorPin) {
        
       Hum_Ground = analogRead(sensorPin);
       delay(1000);
       Hum_Ground = constrain(Hum_Ground, 485, 1023);
       Hum_Ground = map(Hum_Ground, 485, 1023, 100, 0);
       
             
      


}
/*====================== FONCTION  GESTION DES MENUS====================================*/

  void Menu() {
                Serial.println( "menu");
               lcd.clear();
               lcd.setCursor(0,0);
               lcd.print("[1] :Set Temperature");
               lcd.setCursor(0,1);
               lcd.print("[2] :Set RH%");
               lcd.setCursor(0,2);
               lcd.print("[3] :Luminosity ");
               lcd.setCursor(0,3);
               lcd.print("[4] :EXIT ");
               int key_menu = 0;
               
               while (key_menu != 52){
          
                int key_menu = keypad.getKey();
                delay (100);
                if (key_menu != NO_KEY){
                //Serial.println(key_menu);
        switch ( key_menu ) {
              
              case 49: {
                  lcd.clear();
                  
                  lcd.print("Temp consigne : ");    // GESTION DE LA CONSIGNE DE TEMPERATURE
                  temp_cons = ValueRead();
                  lcd.print(temp_cons);
                  break;
              }
              case 50: {
              
                  lcd.clear();
                  
                  lcd.print("RH% consigne : ");     // GESTION DE LA CONSIGNE D'HUMIDITE
                  Hum_cons= ValueRead();
                  lcd.print(Hum_cons);
                  break;
              }
              case 51: {

                  lcd.clear();
                  lcd.print("Luminosity :");          // /!\ A REGLER PLUS TARD
                  int Lum_hours = ValueRead();
                  lcd.print(Lum_hours);
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

     
