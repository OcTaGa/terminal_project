#include <DHT.h>
float t=0;
void setup() {
        Serial.begin(9600);        
}

void loop() {
        DHT dht(2, DHT11);
        dht.begin();
        t = dht.readTemperature();
        Serial.println("Temperature: ");
        Serial.println(t);
}
