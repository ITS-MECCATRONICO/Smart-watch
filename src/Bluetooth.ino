
void Setup_BLE(){
  Serial.println("Adafruit Bluefruit Command <-> Data Mode Example");
  Serial.println("------------------------------------------------");

  /* Initialise the module */
  Serial.print("Initialising the Bluefruit LE module: ");

  if ( !ble.begin(VERBOSE_MODE) )
  {
    Serial.println("******************error_1*******************");
  }
  Serial.println("OK!");

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println("Performing a factory reset: ");
    if ( ! ble.factoryReset() ){
      Serial.println("******************error_2*******************");
    }
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  Serial.println("Please use Adafruit Bluefruit LE app to connect in UART mode");
  Serial.println("Then Enter characters to send to Bluefruit");
  Serial.println();

  ble.verbose(false);  // debug info is a little annoying after this point!

  // Wait for connection 
  while (! ble.isConnected()) {
      delay(500);
  }

  Serial.println("******************************");

  // LED Activity command is only supported from 0.6.6
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    // Change Mode LED Activity
    Serial.println("Change LED activity to " MODE_LED_BEHAVIOUR);
    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
  }

  // Set module to DATA mode
  Serial.println("Switching to DATA mode!");
  ble.setMode(BLUEFRUIT_MODE_DATA);

  Serial.println("******************************");
}
void BLE_send()
{ 
  // Check for user input
  if (QS == true)
  {
    // Send input data to host via Bluefruit
    ble.println(BPM);
    QS = false; 
  }

  
}

