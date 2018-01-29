#include <Event.h>
#include <Timer.h>

#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();
Timer t;
void setup() 
{

  Serial.begin(9600);
  mma.setRange(MMA8451_RANGE_2_G);
  int tickEvent = t.every(2000, doSomething);

}

void loop() 
{
  mma.read();
  Serial.print("X:\t"); Serial.print(mma.x); 
  Serial.print("\tY:\t"); Serial.print(mma.y); 
  Serial.print("\tZ:\t"); Serial.print(mma.z); 
  Serial.println();
  t.update();
}

void doSomething()
{
  Serial.println(millis());
}

