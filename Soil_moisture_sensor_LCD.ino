#include <LiquidCrystal.h> //include the LCD library
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);


int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
 
void setup() {
  lcd.begin(16, 2);
  lcd.print("Humidite");
  // declare the ledPin as an OUTPUT:
   Serial.begin(9600);
}
 
void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  delay(1000);
  Serial.print("sensor = " );
  Serial.println(sensorValue);
  int sensorValue = analogRead(sensorPin) ;
  sensorValue = constrain(sensorValue, 485, 1023);
  sensorValue = map(sensorValue, 485, 1023, 100, 0);
//display final percentage
  lcd.print(sensorValue);
//print the percent symbol at the end
  lcd.print("%");
//wait 0.1 seconds
  delay(75);
//wipe the extra characters
  lcd.print(" ");
  delay (1);
 
}
