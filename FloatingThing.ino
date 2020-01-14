int FloatSensor = D3;
int buttonState = 1;


void setup() 
{
  Serial.begin(9600);
  pinMode(FloatSensor, INPUT_PULLUP);
}

void loop() 
{
   buttonState = digitalRead(FloatSensor);

  if (buttonState == HIGH) 
  {
    Serial.println("Gotin");
  }
  else {
    Serial.println("motin");
  }
  delay(100); 
}
