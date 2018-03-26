#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#include <Wire.h>
#include <I2C.h>
#include <Adafruit_Sensor.h>
#include <MMA8451_n0m1.h>
#include <Adafruit_TMP006.h>

//----------------------------------------------------------------------------------------------------------------------------------------------
//  Variables
const int PIN_INPUT = A0;
const int PIN_BLINK = 13;    // Pin 13 is the on-board LED
const int THRESHOLD = 550;   // Adjust this number to avoid noise when idle
PulseSensorPlayground pulseSensor;

unsigned long lastTime;
unsigned long thisTime;

long tempx, tempy, tempz;//accel

float objt;
float diet;

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

/*int X;
int Y;
int Z;
int acc;
int temp_acc;*/

int BPM_record;
//int B = 0;

bool su_X, su_Y, su_Z;//accel
bool giu_X, giu_Y, giu_Z;//accel
bool Ble = 0;
//----------------------------------------------------------------------------------------------------------------------------------------------
Adafruit_TMP006 tmp006;
MMA8451_n0m1 accel;

//----------------------------------------------------------------------------------------------------------------------------------------------
void setup() {

  Serial.begin(115200);
  Search_TMP006();
  Setup_MMA8451();
  Setup_PS();
  Timer_2_Setup();
  lastTime = millis();
}
//----------------------------------------------------------------------------------------------------------------------------------------------
void loop() {

  Event_MMA8451();
  
  thisTime = millis();
  if(thisTime - lastTime > 4000)
  {
      Event_TMP006();
      lastTime = millis();
      Battery();
  }

  if (pulseSensor.sawStartOfBeat())
  {
    Save_BPM();
    //Serial.print("BPM ");
    Serial.println(pulseSensor.getBeatsPerMinute());
  }
}

void Print()
{
  //Serial.print(X);
  //Serial.print("\t");
  //Serial.print(Y);
  //Serial.print("\t");
  //Serial.println(Z);
  //Serial.print("\t");
  //Serial.print(su_X);
  //Serial.print("\t");
  //Serial.print(PICCO_X);
  //Serial.print("\t");
  //Serial.print(picco_X);
  //Serial.print("\t");
  //Serial.println(freq_X);
  /*Serial.print("\t");
  Serial.print(cont);
  Serial.print("\t");
  Serial.println(millis());*/
}

