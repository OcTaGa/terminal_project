#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

char key;
char temp_read[2] = {0,0};
int temp_cons;

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
void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  Serial.begin(9600);
}

void loop() {
  lcd.clear();
      int i=0;
      while ( i < 2) {
        key = keypad.getKey();
          if (key !=NO_KEY) {

              temp_read[i] = key;
              i++;
            
          }
          else {

              Serial.println(key);
              lcd.print(key);
            
          }
        temp_cons = (temp_read[0]-'0')*10 + (temp_read[1]-'0');
        lcd.setCursor(0,0); 
      }

  Serial.println(temp_cons);
  lcd.print(temp_cons);
      

}
