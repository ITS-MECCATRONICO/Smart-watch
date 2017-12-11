
#include <SPI.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MMA8451.h>
#include "Adafruit_TMP006.h"


#define PROCESSING_VISUALIZER 1
#define SERIAL_PLOTTER  2

#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"
//----------------------------------------------------------------------------------------------------------------------------------------------                      
//  Variables
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin

unsigned long lastTime; 
unsigned long thisTime;
float objt;
float diet;

long X;
long Y;
long Z;

int BPM_record[100];
int B = 0;

// Volatile Variables, used in the interrupt service routine!
int BPM;              // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;        // becomes true when Arduino finds a beat.

// SET THE SERIAL OUTPUT TYPE TO YOUR NEEDS
// PROCESSING_VISUALIZER works with Pulse Sensor Processing Visualizer
//      https://github.com/WorldFamousElectronics/PulseSensor_Amped_Processing_Visualizer
// SERIAL_PLOTTER outputs sensor data for viewing with the Arduino Serial Plotter
//      run the Serial Plotter at 9600 baud: Tools/Serial Plotter or Command+L
static int outputType = SERIAL_PLOTTER;
//----------------------------------------------------------------------------------------------------------------------------------------------           
Adafruit_MMA8451 mma = Adafruit_MMA8451();
Adafruit_TMP006 tmp006;

SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);
Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN, BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);
//----------------------------------------------------------------------------------------------------------------------------------------------
void setup(void) {
  
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  pinMode(fadePin,OUTPUT);          // pin that will fade to your heartbeat!
  
  Serial.begin(115200);
  Search_TMP006();
  Search_MMA8451();
  Setup_BLE();
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS
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

  //Serial.print("\t"); Serial.print(X); Serial.print("\t"); Serial.print(Y); Serial.print("\t"); Serial.print(Z); Serial.print("\t");
  //Serial.print("\t"); Serial.print(objt); Serial.print("\t"); Serial.print(diet); Serial.print("\t") 
  
  BLE_send();

  // Echo received data
  while ( ble.available() )
  {
    int c = ble.read();

    Serial.print((char)c);
  }
}

 
