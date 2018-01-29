#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_TMP006.h>

#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"
//----------------------------------------------------------------------------------------------------------------------------------------------
//  Variables
const int PIN_INPUT = A0;
const int PIN_BLINK = 13;    // Pin 13 is the on-board LED
const int THRESHOLD = 550;   // Adjust this number to avoid noise when idle
PulseSensorPlayground pulseSensor;

unsigned long lastTime;
unsigned long thisTime;

float objt;
float diet;

int X;
int Y;
int Z;
int acc;
int temp_acc;

int BPM_record;
//int B = 0;

bool Ble = 0;
//----------------------------------------------------------------------------------------------------------------------------------------------
Adafruit_MMA8451 mma = Adafruit_MMA8451();
Adafruit_TMP006 tmp006;

SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);
Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN, BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);
//----------------------------------------------------------------------------------------------------------------------------------------------
void setup() {

  Serial.begin(115200);
  Search_TMP006();
  Search_MMA8451();
  Setup_PS();
  Setup_BLE();
  lastTime = millis();
}
//----------------------------------------------------------------------------------------------------------------------------------------------
void loop() {
  
  Event_MMA8451();
  acc = X + Y + Z;
  //Serial.print("ACC ");
  //Serial.println(acc);

  BLE_conn();

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
    //Serial.println(pulseSensor.getBeatsPerMinute());
  }

  // Echo received data
  while ( ble.available() )
  {
    int c = ble.read();

    Serial.print((char)c);
  }
}
