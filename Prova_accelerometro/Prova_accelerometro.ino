#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <TimerOne.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

int Ax[100], Ay[100], Az[100];
int index = 0, i = 0;
int X, Y, Z;
long tempx, tempy, tempz;

void setup()
{

  Serial.begin(9600);
  Serial.println("Adafruit MMA8451 test!");
  
  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  
  mma.setRange(MMA8451_RANGE_2_G);

  Timer1.initialize(100000);
  Timer1.attachInterrupt(interr); // blinkLED to run every 500 ms

}

void loop() 
{
  mma.read();

  Ax[index] = mma.x;
  Ay[index] = mma.y;
  Az[index] = mma.z;
  
  index++;

}

void interr()
{
  
  tempx = 0;
  tempy = 0;
  tempz = 0;

  for(i = 0; i < index;  i++)
  {
    tempx = tempx + Ax[i];
    tempy = tempy + Ay[i];
    tempz = tempz + Az[i];

    Ax[i] = 0;
    Ay[i] = 0;
    Az[i] = 0;
  }

  X = tempx / index;
  Y = tempy / index;
  Z = tempz / index;

  //Serial.println(micros());
  //Serial.println(x[5]);
  Serial.print(X);
   Serial.print("\t");
  Serial.print(Y);
   Serial.print("\t");
  Serial.println(Z);
  //Serial.println(index);
  
  index = 0;
  
  //Serial.println("-----------------------------------------------------");

}// end interr

