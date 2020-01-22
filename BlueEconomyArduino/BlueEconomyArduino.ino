#include <Blynk.h>

/*
  This is example code that is used in a project about blue economy, watering plants and trees. We have used NodeMCU as our
  main microcontroller, you can use any arduino or any clone that you want. The code is compatible with different types of DHT
  sensor (we use DHT11). Simpe float switch and photoresistor. If you have any problems or questions you can issue 
  them on https://github.com/DPDyakov18/BlueEconomy2020Project/tree/master.

  Author:
  Dimitar Dyakov 

  Last modified: 19/01/2020
*/

// Library for DHT11 | DHT21 | DHT22
#include "DHT.h"
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <Adafruit_MCP3008.h>
// Used to define which sensor we use
#define DHTTYPE DHT11

#define BLYNK_PRINT Serial

Adafruit_MCP3008 adc;

// Initializing the pin for the float switch
int FloatSensor = D1;
int buttonState = 1;
char ssid[] = "";
char pass[] = "";
char auth[] = "";
// Initializing the pin for the photoresistor
const int pResistor = A0;
int count = 0;
int value;

// Defining the DHT sensor pin
#define dht_dpin D2
// Method used for the DHT sensor
DHT dht(dht_dpin, DHTTYPE);
BlynkTimer timer;

void setup()
{
  dht.begin();
  
  // Bandwidth that will be used to use the serial monitor (should be matching with the bandwith in the serial monitor menu)
  Serial.begin(9600);
  adc.begin();
  Blynk.begin(auth, ssid, pass);
  while (!Serial);
  // Set up the pins that are used
  pinMode(FloatSensor, INPUT_PULLUP);
  pinMode(pResistor, INPUT);
  pinMode(D0, OUTPUT);
  timer.setInterval(1000L, myTimerEvent);
  digitalWrite(D0, HIGH);
  delay(2000);
  digitalWrite(D0, LOW);
  delay(2000);
}

void myTimerEvent()
{
  int li = adc.readADC(1);
  Blynk.virtualWrite(V5, li);
}


void DigToAn()
{
    for (int chan=0; chan<8; chan++) 
    {
    Serial.print(adc.readADC(chan)); Serial.print("\t");
    }
    Serial.print("["); Serial.print(count); Serial.println("]");
    count++;
    delay(1000);
};

// Function for the DHT sensor
void tmph()
{
    // Variable used to display the humidity and the temperature
    float h = dht.readHumidity();
    float t = dht.readTemperature();     
    // Printing the humidity and the temperature in the serial monitor    
    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("temperature = ");
    Serial.print(t); 
    Blynk.virtualWrite(V6, t);
    Blynk.virtualWrite(V7, h);
    // Delay to debug the sensor and the serial monitor
    delay(900);
};

// Function for the float switch
void floater()
{
  // Setting the variable to 1 if there is no water or zero if there is some water
  buttonState = digitalRead(FloatSensor);
  // Displaying in the serial monitor the state of the float switch
  if (buttonState == HIGH) 
  {
    Serial.println("No water");
  }
  else
  {
    Serial.println("Has water");
  }
  // Delay for debug
  Blynk.virtualWrite(V8, "No water");
  delay(100);
};

void loop()
{
  // Variable that takes the value of the photoresistor
  int value = analogRead(pResistor);
  
  // Displaying the photoresistor sensor in the serial monitor
  Serial.println(value);
  Serial.println();
  // Calling the functions
  tmph();
  floater();
  DigToAn();
  Blynk.run();
  timer.run();
}
