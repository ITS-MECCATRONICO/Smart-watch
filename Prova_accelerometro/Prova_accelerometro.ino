#include <Wire.h>
#include <I2C.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TMP006.h"
#include <MMA8451_n0m1.h>

Adafruit_TMP006 tmp006;
MMA8451_n0m1 accel;

bool su_X, su_Y, su_Z;
bool giu_X, giu_Y, giu_Z;

int Ax_1[30], Ay_1[30], Az_1[30];
int Ax_2[30], Ay_2[30], Az_2[30];
int index_1, index_2, cont = 1, cont_1_s;
int X, Y, Z;
int PICCO_X, PICCO_Y, PICCO_Z;
int picco_X, picco_Y, picco_Z;
int last_X, last_Y, last_Z;
int last_osc_X, last_osc_Y, last_osc_Z;
int Osc_X, Osc_Y, Osc_Z;
int freq_X, freq_Y, freq_Z;
int diet;

unsigned long lastTime;
unsigned long thisTime;

long tempx, tempy, tempz;

void setup()
{

  Serial.begin(57600);
  
  Serial.println("Adafruit TMP006 example");
  if (! tmp006.begin()) 
  {
    Serial.println("No sensor found");
    while (1);
  }

  accel.setI2CAddr(0x1D); //change your device address if necessary, default is 0x1C
  accel.dataMode(true, 2); //enable highRes 10bit, 2g range [2g,4g,8g]
  Serial.println("MMA8451_n0m1 library");
  Serial.println("XYZ Data Example");
  Serial.println("n0m1.com");

  lastTime = millis();
  Timer_1_Setup();
  
}

void loop() 
{

  if (index_1 >= 25)
    Media_1();

  else if (index_2 >= 25)
    Media_2();

  Picco();

  thisTime = millis();
  if(thisTime - lastTime > 4000)
  {
    diet = tmp006.readDieTempC();
    lastTime = millis();
  }

  Print();
}

ISR(TIMER1_OVF_vect)
{
  cli();

  accel.update();

  if (cont == 1)
  {
    Ax_1[index_1] = accel.x();
    Ay_1[index_1] = accel.y();
    Az_1[index_1] = accel.z();
    
    index_1++;

    if (index_1 == 25)
      cont = 2;
  }

  else if (cont == 2)
  {
    Ax_2[index_2] = accel.x();
    Ay_2[index_2] = accel.y();
    Az_2[index_2] = accel.z();
    
    index_2++;

    if (index_2 == 25)
      cont = 1;
  }

  if (cont_1_s >= 500)//CONTEGGIO IMPULSI IN UN SECONDO
  {
    freq_X = Osc_X;
    Osc_X = 0;

    freq_Y = Osc_Y;
    Osc_Y = 0;

    freq_Z = Osc_Z;
    Osc_Z = 0;
    
    cont_1_s = 0;
  }

  cont_1_s ++;
  
  sei();
}// end int_1

void Media_1()
{
    tempx = 0;
    tempy = 0;
    tempz = 0;
  
    for(int i = 0; i < index_1;  i++)
    {
      tempx = tempx + Ax_1[i];
      tempy = tempy + Ay_1[i];
      tempz = tempz + Az_1[i];
  
      Ax_1[i] = 0;
      Ay_1[i] = 0;
      Az_1[i] = 0;
    }//end for(i = 0; i < index_1;  i++)
  
    X = tempx / index_1;
    Y = tempy / index_1;
    Z = tempz / index_1;
     
    index_1 = 0;  
}

void Media_2()
{
    tempx = 0;
    tempy = 0;
    tempz = 0;
  
    for(int i = 0; i < index_2;  i++)
    {
      tempx = tempx + Ax_2[i];
      tempy = tempy + Ay_2[i];
      tempz = tempz + Az_2[i];
  
      Ax_2[i] = 0;
      Ay_2[i] = 0;
      Az_2[i] = 0;
    }//end for(i = 0; i < index_2;  i++)
  
    X = tempx / index_2;
    Y = tempy / index_2;
    Z = tempz / index_2;
     
    index_2 = 0;  
}

void Picco()
{
    volatile int this_X, this_Y, this_Z;

    this_X = X;
    this_Y = Y;
    this_Z = Z;
    
//----------------------------------------------------X
    if (this_X > last_X + 500)//picco su
    {
      su_X = 1;
      giu_X = 0;
    }
    else if (this_X < last_X - 500)//picco giu
    {
      su_X = 0;
      giu_X = 1;
    }

    if (su_X == 1 && this_X > last_X)
      PICCO_X = this_X;
      
     else if (giu_X == 1 && this_X < last_X)
      picco_X = this_X;

    if (last_osc_X != su_X)
    {
      Osc_X ++;
      last_osc_X = su_X;
    }
    
//---------------------------------------------------Y
    if (this_Y > last_Y + 500)//picco su
    {
      su_Y = 1;
      giu_Y = 0;
    }
    else if (this_Y < last_Y - 500)//picco giu
    {
      su_Y = 0;
      giu_Y = 1;
    }

    if (su_Y == 1 && this_Y > last_Y)
      PICCO_Y = this_Y;
      
     else if (giu_Y == 1 && this_Y < last_Y)
      picco_Y = this_Y;

    if (last_osc_Y != su_Y)
    {
      Osc_Y ++;
      last_osc_Y = su_Y;
    }

//---------------------------------------------------Z
    if (this_Z > last_Z + 500)//picco su
    {
      su_Z = 1;
      giu_Z = 0;
    }
    else if (this_Z < last_Z - 500)//picco giu
    {
      su_Z = 0;
      giu_Z = 1;
    }

    if (su_Z == 1 && this_Z > last_Z)
      PICCO_Z = this_Z;
      
     else if (giu_Z == 1 && this_Z < last_Z)
      picco_Z = this_Z;

    if (last_osc_Z != su_Z)
    {
      Osc_Z ++;
      last_osc_Z = su_Z;
    }

    last_X = this_X;
    last_Y = this_Y;
    last_Z = this_Z;
}

void Print()
{
  Serial.print(X);
  Serial.print("\t");
  /*Serial.print(Y);
  Serial.print("\t");
  Serial.print(Z);
  Serial.print("\t");*/
  Serial.print(su_X);
  Serial.print("\t");
  Serial.print(PICCO_X);
  Serial.print("\t");
  Serial.print(picco_X);
  Serial.print("\t");
  Serial.println(freq_X);
  /*Serial.print("\t");
  Serial.print(cont);
  Serial.print("\t");
  Serial.println(millis());*/
}

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

