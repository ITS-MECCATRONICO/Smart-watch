void Battery() 
{
  // read the input on analog pin 1:
  int sensorValue = analogRead(A1);
  
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (6.6 / 1023.0);
  
  // print out the value you read:
  ble.println(sensorValue);
}
