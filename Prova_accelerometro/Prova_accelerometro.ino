#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

int cont = 0;
int x[200], y[200], z[200];
int index = 0, i = 0;
int tempx, tempy, tempz;

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
  
  interruptSetup();

}

void loop() 
{
  mma.read();

  x[index] = mma.x;
  y[index] = mma.y;
  z[index] = mma.z;
  
  index++;

}

ISR(TIMER2_COMPA_vect)
{
  cli();
  cont++;
  //Serial.println(micros());

  if(cont == 500) //con 50 ogni 100ms
  {
    for(i = 0; i++; i < index)
    {
      tempx = tempx + x[i];
      tempy = tempy + y[i];
      tempz = tempz + z[i];
    }

    tempx = tempx / index;
    tempy = tempy / index;
    tempz = tempz / index;

    //Serial.println(micros());
    Serial.println(tempz);

    tempx = 0;
    tempy = 0;
    tempz = 0;
    
    index = 0;
    cont = 0;
  }
  sei();
}// end isr

void interruptSetup()
{
    // Initializes Timer2 to throw an interrupt every 2mS.
    TCCR2A = 0x02;     // DISABLE PWM ON DIGITAL PINS 3 AND 11, AND GO INTO CTC MODE
    TCCR2B = 0x05;     // DON'T FORCE COMPARE, 128 PRESCALER
    OCR2A = 0X7c;      // SET THE TOP OF THE COUNT TO 124 FOR 500Hz SAMPLE RATE
    TIMSK2 = 0x02;     // ENABLE INTERRUPT ON MATCH BETWEEN TIMER2 AND OCR2A
    sei();             // MAKE SURE GLOBAL INTERRUPTS ARE ENABLED
 }
