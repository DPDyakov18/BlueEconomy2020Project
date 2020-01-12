#include "DHT.h"
#define DHTTYPE DHT11

const int pResistor = A0;
int value;

#define dht_dpin D1
DHT dht(dht_dpin, DHTTYPE);

void setup(){
  dht.begin();
  Serial.begin(9600);
  delay(700);
 pinMode(pResistor, INPUT);
  Serial.begin(9600);
}


void loop(){
  int value = analogRead(pResistor);
  Serial.println(value);

    float h = dht.readHumidity();
    float t = dht.readTemperature();         
    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
    delay(800);
}
