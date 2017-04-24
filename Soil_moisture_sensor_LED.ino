int output_value ;

int led_pin =13;

int sensor_pin =A0;

void setup() {

    Serial.begin(9600);

    Serial.println("Reading From the Sensor ...");

    delay(2000);

    pinMode(led_pin, OUTPUT);

    pinMode(sensor_pin, INPUT);

}

void loop() {
  
 output_value= analogRead(sensor_pin);

 output_value = map(output_value,550,0,0,100);

 Serial.print("Moisture : ");

 Serial.print(output_value);

 Serial.println("%");

 delay(1000);

 if(digitalRead(sensor_pin) == HIGH){

 digitalWrite(led_pin, LOW);

 } else {

  digitalWrite(led_pin, HIGH);

  delay(1000);
 }
}
