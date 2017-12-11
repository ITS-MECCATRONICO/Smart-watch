
void Search_TMP006(){  
  Serial.println("Adafruit TMP006 test!");
  if (! tmp006.begin()) {
    Serial.println("No sensor found");
    while (1);
  }
  Serial.println("TMP006 found!");
  Serial.println("Send s to enter sleep mode, or w to wake up.  Measurements are not updated while asleep!");
}

void Sleep_TMP006(){
  // Check for sleep/wake command.
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == 'w') {
      Serial.println("Waking up!");
      tmp006.wake();
    }
    else if (c == 's') {
      Serial.println("Going to sleep!");
      tmp006.sleep();
    }
  } 
}

void Event_TMP006(){
    objt = tmp006.readObjTempC();
    diet = tmp006.readDieTempC();
        
    /*Serial.print("Object Temperature: "); 
    Serial.print(objt); 
    Serial.println("°C");
    Serial.print("Die Temperature: "); 
    Serial.print(diet); 
    Serial.println("°C");
    
    Serial.println();*/
}
