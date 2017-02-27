#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

float temp=0;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
        lcd.begin();
        //Serial.begin(9600);        
}

void loop() {
        DHT dht(2, DHT11);
        dht.begin();
        temp = dht.readTemperature();
        lcd.noCursor();
        
        lcd.print("temperature: ");
        //Serial.println("Temperature: ");
        //Serial.println(temp);
        //lcd.setCursor(0, 1);
        lcd.print(temp);
        delay(2000);
}
