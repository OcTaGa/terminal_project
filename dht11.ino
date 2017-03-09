#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

float t = 0;
float h = 0;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
        lcd.begin();
        lcd.setCursor(0, 0);
        lcd.print("Temp : ");       
        
        //Serial.begin(9600);        
}

void loop() {
        DHT dht(2, DHT11);
        dht.begin();
        t = dht.readTemperature();
        h = dht.readHumidity();
        lcd.setCursor(7, 0);
        lcd.clear();
        lcd.print(t);
        //Serial.println("Temperature: ");
        //Serial.println(temp);
        //lcd.setCursor(0, 1);
        lcd.print(t);
        delay(2000);
}
