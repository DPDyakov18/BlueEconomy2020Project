#include "DHT.h"
#define DHTTYPE DHT11

int FloatSensor = D3;
int buttonState = 1;
const int pResistor = A0;
int value;

#define dht_dpin D1
DHT dht(dht_dpin, DHTTYPE);

void setup(){
  dht.begin();
  Serial.begin(9600);
  pinMode(FloatSensor, INPUT_PULLUP);
  pinMode(pResistor, INPUT);
}

void tmph()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature();         
    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
    delay(800);
};

void Floater()
{
  buttonState = digitalRead(FloatSensor);
  if (buttonState == HIGH) 
  {
    Serial.println("No water");
  }
  else
  {
    Serial.println("Has water");
  }
  delay(100);
};

void loop(){
  int value = analogRead(pResistor);
  Serial.println(value);
  tmph();
  Floater();
}
