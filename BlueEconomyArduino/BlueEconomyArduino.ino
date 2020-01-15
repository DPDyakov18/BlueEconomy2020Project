/*
  This is example code that is used in a project about blue economy, watering plants and trees. We have used NodeMCU as our
  main microcontroller, you can use any arduino or any clone that you want. The code is compatible with different types of DHT
  sensor (we use DHT11). Simpe float switch and photoresistor. If you have any problems or questions you can issue 
  them on https://github.com/DPDyakov18/BlueEconomy2020Project/tree/master.

  Code written by:
  Dimitar Dyakov 

  Last modified: 15/01/2020
*/

// Library for DHT11 | DHT21 | DHT22
#include "DHT.h"
// Used to define which sensor we use
#define DHTTYPE DHT11

// Initializing the pin for the float switch
int FloatSensor = D3;
int buttonState = 1;
// Initializing the pin for the photoresistor
const int pResistor = A0;
int value;

// Defining the DHT sensor pin
#define dht_dpin D1
// Method used for the DHT sensor
DHT dht(dht_dpin, DHTTYPE);

void setup()
{
  dht.begin();
  // Bandwith that will be used to use the serial monitor (should be matching with the bandwith in the serial monitor menu)
  Serial.begin(9600);
  // Set up the pins that are used
  pinMode(FloatSensor, INPUT_PULLUP);
  pinMode(pResistor, INPUT);
}

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
  delay(100);
};

void loop()
{
  // Variable that takes the value of the photoresistor
  int value = analogRead(pResistor);
  // Displaying the photoresistor sensor in the serial monitor
  Serial.println(value);
  // Calling the functions
  tmph();
  floater();
}
