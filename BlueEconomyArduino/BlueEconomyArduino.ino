 /*
  This is example code that is used in a project about blue economy, watering plants and trees. We have used NodeMCU as our
  main microcontroller, you can use any arduino or any clone that you want. The code is compatible with different types of DHT
  sensor (we use DHT11). Simpe float switch and photoresistor. If you have any problems or questions you can issue 
  them on https://github.com/DPDyakov18/BlueEconomy2020Project/tree/master.

  Author:
  Dimitar Dyakov 

  Last modified: 05/02/2020
*/

// Blynk library
#include <Blynk.h>
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
int FloatSensor = D2;
// Initializing the pin for the pump
int Pump = D3;
// Ssid of your network
char ssid[] = " ";
// Pass of your network
char pass[] = " ";
// Authentication code received from Blynk
char auth[] = " ";
// Initializing the pin for the photoresistor
const int pResistor = A0;
//int count = 0;
// Variables to create delay
unsigned long int lastRead_th;
unsigned long int lastRead_fs;
unsigned long int lastRead_da;
unsigned long int lastRead_sm;
unsigned long int lastRead_hu;
unsigned long int lastRead_pu;
// Variable used for the pump
bool pumpEnabled = false;

// Defining the DHT sensor pin
#define dht_dpin D4
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
  pinMode(Pump, OUTPUT);
  // Starting the timer
  timer.setInterval(1000L, myTimerEvent);
  
  lastRead_th = millis();
  lastRead_fs = millis();
  lastRead_da = millis();
  lastRead_sm = millis();
  lastRead_hu = millis();
  lastRead_pu = millis();
}

// Function for the soil moisture sensor
void soilMoistureFN()
{
  // Creating the delay
  if (millis() - lastRead_sm > 1000)
  {
    lastRead_sm = millis();
    int li = adc.readADC(1);
    Serial.println(adc.readADC(1));
    // Sending the information to Blynk
    Blynk.virtualWrite(V5, li);
  }
}

/*void DigToAn()
{
  if (millis() - lastRead_da > 100)
  {
    lastRead_da = millis();
    for (int chan=0; chan<8; chan++) 
    {
      Serial.print(adc.readADC(chan)); Serial.print("\t");
    }
    
    Serial.print("["); Serial.print(count); Serial.println("]");
    count++;
  }
};
*/

// Function for the DHT sensor
void tmph()
{
    if (millis() - lastRead_sm > 1000)
   {
      lastRead_sm = millis();
      // Variable used to display the humidity and the temperature
      float h = dht.readHumidity();
      float t = dht.readTemperature();     
      // Printing the humidity and the temperature in the serial monitor    
      Serial.print("Current humidity = ");
      Serial.print(h);
      Serial.print("temperature = ");
      Serial.print(t); 
      // Sending the information to Blynk
      Blynk.virtualWrite(V6, t);
      Blynk.virtualWrite(V7, h);
    }
};

// Function for the float switch
void floater()
{
  if (millis() - lastRead_fs > 1000)
  {
    lastRead_fs = millis();
    // Setting the variable to 1 if there is no water or zero if there is some water
    int buttonState = digitalRead(FloatSensor);
    // Displaying the status of the water
    if (buttonState == HIGH) 
    {
      Serial.println(buttonState);
      Blynk.virtualWrite(V8, "Has water");
    }
    else
    {
      Serial.println(buttonState);
      Blynk.virtualWrite(V8, "No water");
    }
  }
};

void loop()
{
  if (millis() - lastRead_hu > 2000){
    lastRead_hu = millis();
    // If statement to see if the pump should be turned on
    if(adc.readADC(1) > 300)
    {
      Serial.println("Turning pump on");
      digitalWrite(Pump, HIGH);
      pumpEnabled = true;
    } else {
      pumpEnabled = false;  
      digitalWrite(Pump, LOW);
    }
  }
  // Creating delay
  if (pumpEnabled == true && millis() - lastRead_pu > 10000){
    Serial.println("Turning pump off");
    digitalWrite(Pump, LOW);
  }
  
  // Variable that takes the value of the photoresistor
  int value = analogRead(pResistor);
  
  // Displaying the photoresistor sensor in the serial monitor
  //Serial.println(value);
  //Serial.println();

  tmph();
  floater();
  //DigToAn();
  soilMoistureFN();
  
  Blynk.run();
  timer.run();
}
