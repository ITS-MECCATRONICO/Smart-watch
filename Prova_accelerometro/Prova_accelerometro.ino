#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

int cont = 0;
void setup() 
{

  Serial.begin(9600);
  
  mma.setRange(MMA8451_RANGE_2_G);
  
  // Initializes Timer2 to throw an interrupt every 2mS.
  TCCR2A = 0x02;     // DISABLE PWM ON DIGITAL PINS 3 AND 11, AND GO INTO CTC MODE
  TCCR2B = 0x05;     // DON'T FORCE COMPARE, 128 PRESCALER
  OCR2A = 0X7C;      // SET THE TOP OF THE COUNT TO 124 FOR 500Hz SAMPLE RATE
  TIMSK2 = 0x02;     // ENABLE INTERRUPT ON MATCH BETWEEN TIMER2 AND OCR2A
  sei();             // MAKE SURE GLOBAL INTERRUPTS ARE ENABLED
}

void loop() 
{
  
}

ISR(TIMER2_COMPA_vect)
{
  cli(); 
  cont++;

  if(cont == 500)
  {
    Serial.println(millis());
    mma.read();
  Serial.print(mma.x); 
  Serial.print(mma.y); 
  Serial.println(mma.z);
    cont = 0;
  }
  sei();
}// end isr
