
void Setup_PS()
{
  // Configure the PulseSensor manager.

  pulseSensor.analogInput(PIN_INPUT);
  pulseSensor.blinkOnPulse(PIN_BLINK);
  pulseSensor.setThreshold(THRESHOLD);

  while(!pulseSensor.begin());

  Serial.println("Pulse Sensor setup OK!!");
}

