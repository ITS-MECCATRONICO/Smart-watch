#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <TimerOne.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

int Ax[100], Ay[100], Az[100];
<<<<<<< HEAD
int index = 0, cont = 0;
=======
int index = 0, i = 0;
>>>>>>> 3e64ccd50c1a7d97c4b3ae866c1b84033ca942c9
int X, Y, Z;
long tempx, tempy, tempz;

void setup()
{

  Serial.begin(9600);
  Serial.println("Adafruit MMA8451 test!");
  
  if (! mma.begin()) 
  {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  
  mma.setRange(MMA8451_RANGE_2_G);

<<<<<<< HEAD
  Timer_2_Setup();
=======
  Timer1.initialize(100000);
 
  Timer1.attachInterrupt(int_1); // blinkLED to run every 500 ms
>>>>>>> 3e64ccd50c1a7d97c4b3ae866c1b84033ca942c9

}

void loop() 
{
<<<<<<< HEAD
=======
  mma.read();

  Ax[index] = mma.x;
  Ay[index] = mma.y;
  Az[index] = mma.z;
>>>>>>> 3e64ccd50c1a7d97c4b3ae866c1b84033ca942c9
  
}

void int_1()
{
<<<<<<< HEAD

  mma.read();

  Ax[index] = mma.x;
  Ay[index] = mma.y;
  Az[index] = mma.z;
  
  index++;

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
    Serial.println(index);
     
    index = 0;
    
    //Serial.println("-----------------------------------------------------");

  }//end if (cont >= 50)
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

=======
  
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
  Serial.println(index);
  
  
  index = 0;
  
  //Serial.println("-----------------------------------------------------");

}// end int_1

>>>>>>> 3e64ccd50c1a7d97c4b3ae866c1b84033ca942c9
