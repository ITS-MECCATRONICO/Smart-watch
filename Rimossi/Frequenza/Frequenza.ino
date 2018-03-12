boolean state = 0;
boolean alert = 0;
unsigned int pulseCount = 0;
unsigned long time0 = 0;
unsigned long timeT = 0;
unsigned long frequency = 0;


void setup() 
{
  pinMode(7, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  state = digitalRead(7);
  
  if (state == LOW) 
  {
    alert = 1;
  }
  
  if (state == HIGH && alert == 1 && pulseCount == 0) 
  {
    time0 = millis();
  }
  
  if (state == HIGH && alert == 1) 
  {
    pulseCount = (pulseCount + 1);
    alert = 0;
  }
  
  if (pulseCount == 1000) 
  {
    timeT = millis();
    frequency = 1000000/(timeT-time0);
    Serial.print("frequenza = ");
    Serial.print(frequency);
    Serial.println(" Hz");
    pulseCount = 0;
    alert = 0;
  }

}
