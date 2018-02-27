#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TMP006.h"
#include <I2C.h>
#include <MMA8451_n0m1.h>

Adafruit_TMP006 tmp006;
MMA8451_n0m1 accel;

unsigned long lastTime;
unsigned long thisTime;

int Ax[100], Ay[100], Az[100];
int index = 0, cont;
int X, Y, Z;
int diet;

long tempx, tempy, tempz;

void setup()
{

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Adafruit TMP006 example");
  if (! tmp006.begin()) 
  {
    Serial.println("No sensor found");
    while (1);
  }
  
  lastTime = millis();

  accel.setI2CAddr(0x1D); //change your device address if necessary, default is 0x1C
  accel.dataMode(true, 2); //enable highRes 10bit, 2g range [2g,4g,8g]
  Serial.println("MMA8451_n0m1 library");
  Serial.println("XYZ Data Example");
  Serial.println("n0m1.com");

  Timer_2_Setup();
  
}

void loop() 
{

  thisTime = millis();
  if(thisTime - lastTime > 4000)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    diet = tmp006.readDieTempC();
    lastTime = millis();
  }
  
}

ISR(TIMER2_COMPA_vect)
{
  cli();

  accel.update();
  
  Ax[index] = accel.x();
  Ay[index] = accel.y();
  Az[index] = accel.z();
  
  index++;
  cont++;
  if (cont >= 50)
  {
    tempx = 0;
    tempy = 0;
    tempz = 0;
  
    for(int i = 0; i < index;  i++)
    {
      tempx = tempx + Ax[i];
      tempy = tempy + Ay[i];
      tempz = tempz + Az[i];
  
      Ax[i] = 0;
      Ay[i] = 0;
      Az[i] = 0;
    }//end for(i = 0; i < index;  i++)
  
    X = tempx / index;
    Y = tempy / index;
    Z = tempz / index;
  
    //Serial.println(micros());
    //Serial.println(x[5]);
    Serial.print(X);
    Serial.print("\t");
    Serial.print(Y);
    Serial.print("\t");
    Serial.print(Z);
    Serial.print("\t");
    Serial.print(cont);
    Serial.print("\t");
    Serial.println(index);
     
    index = 0;
    cont = 0;
    
    //Serial.println("-----------------------------------------------------");

  }//end if (cont >= 50)
  sei();
}// end int_1

void Timer_1_Setup() //ISR(TIMER1_OVF_vect)
{
  // Initializes Timer1 to throw an interrupt every 2mS.
  TCCR1A = 0x00; // DISABLE OUTPUTS AND PWM ON DIGITAL PINS 9 & 10
  TCCR1B = 0x11; // GO INTO 'PHASE AND FREQUENCY CORRECT' MODE, NO PRESCALER
  TCCR1C = 0x00; // DON'T FORCE COMPARE
  TIMSK1 = 0x01; // ENABLE OVERFLOW INTERRUPT (TOIE1)
  ICR1 = 8000;  // TRIGGER TIMER INTERRUPT EVERY 2mS
  sei();         // MAKE SURE GLOBAL INTERRUPTS ARE ENABLED
}

void Timer_2_Setup() //ISR(TIMER2_COMPA_vect)
{ 
  // Initializes Timer2 to throw an interrupt every 2mS.
  TCCR2A = 0x02;     // DISABLE PWM ON DIGITAL PINS 3 AND 11, AND GO INTO CTC MODE
  TCCR2B = 0x05;     // DON'T FORCE COMPARE, 128 PRESCALER
  OCR2A = 0X7C;      // SET THE TOP OF THE COUNT TO 124 FOR 500Hz SAMPLE RATE
  TIMSK2 = 0x02;     // ENABLE INTERRUPT ON MATCH BETWEEN TIMER2 AND OCR2A
  sei();             // MAKE SURE GLOBAL INTERRUPTS ARE ENABLED
}

