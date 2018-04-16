
#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

//-------------------------------------------------------------------------
    #define FACTORYRESET_ENABLE         0
    #define MINIMUM_FIRMWARE_VERSION    "0.6.6"
    #define MODE_LED_BEHAVIOUR          "MODE"
//=========================================================================

// Create the bluefruit object, either software serial...uncomment these lines

SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);
Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN, BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);

int NUM = 0;

void setup(void)
{
  while (!Serial);  // required for Flora & Micro
  delay(500);

  Serial.begin(115200);

  Setup_BLE();
  BLE_conn();
}

void loop(void)
{
  delay(1000);
  
  ble.println(NUM);
  Serial.println(NUM);

  NUM ++;
  
  // Echo received data
  while ( ble.available() )
  {
    int c = ble.read();

    Serial.print((char)c);
  }
}

void Setup_BLE()
{
  Serial.println("Adafruit Bluefruit Setup");

  if ( !ble.begin(VERBOSE_MODE) )
  {
    Serial.println("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?");
  }
  Serial.println("OK!");

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println("Performing a factory reset: ");
    if ( ! ble.factoryReset() ){
      Serial.println("Couldn't factory reset");
    }
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Please connect in UART mode");

  ble.verbose(false);  // debug info is a little annoying after this point!
}

void BLE_conn()
{
  /* Wait for connection */
  while (! ble.isConnected()) {
      delay(500);
  }

  Serial.println("******************************");

  // LED Activity command is only supported from 0.6.6
  if (ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION))
  {
    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
  }

  // Set module to DATA mode
  Serial.println("Switching to DATA mode!");
  ble.setMode(BLUEFRUIT_MODE_DATA);

  Serial.println("******************************");
}
  
