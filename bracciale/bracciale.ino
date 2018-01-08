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
#include "Adafruit_TMP006.h"

#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"
//----------------------------------------------------------------------------------------------------------------------------------------------
//  Variables
const int OUTPUT_TYPE = SERIAL_PLOTTER;
const int PIN_INPUT = A0;
const int PIN_BLINK = 13;    // Pin 13 is the on-board LED
const int PIN_FADE = 5;
const int THRESHOLD = 550;   // Adjust this number to avoid noise when idle
PulseSensorPlayground pulseSensor;

unsigned long lastTime;
unsigned long thisTime;

float objt;
float diet;

long X;
long Y;
long Z;

int BPM_record[100];
int B = 0;
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
  Setup_BLE();
  Setup_PS();
  lastTime = millis();
  if (!pulseSensor.begin()) {
    /*
       PulseSensor initialization failed,
       likely because our particular Arduino platform interrupts
       aren't supported yet.

       If your Sketch hangs here, try ProcessEverySample.ino,
       which doesn't use interrupts.
    */
    for(;;) {
      // Flash the led to show things didn't work.
      digitalWrite(PIN_BLINK, LOW);
      delay(50);
      digitalWrite(PIN_BLINK, HIGH);
      delay(50);
    }
  }
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
    ble.print("BPM ");
    ble.println(pulseSensor.getBeatsPerMinute());
  }

  //Serial.print("\t"); Serial.print(X); Serial.print("\t"); Serial.print(Y); Serial.print("\t"); Serial.print(Z); Serial.print("\t");
  //Serial.print("\t"); Serial.print(objt); Serial.print("\t"); Serial.print(diet); Serial.print("\t")

  // Echo received data
  while ( ble.available() )
  {
    int c = ble.read();

    Serial.print((char)c);
  }
}
