
void Search_MMA8451(){  
  Serial.println("Adafruit MMA8451 test!");
  if (!mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  
  mma.setRange(MMA8451_RANGE_2_G);
  Serial.print("Range = "); 
  Serial.print(2 << mma.getRange());  
  Serial.println("G");
}

void Event_MMA8451(){
  // Get a new sensor event
  /*sensors_event_t event; 
  mma.getEvent(&event);
  // Display the results (acceleration is measured in m/s^2)
  Serial.print("X: \t"); Serial.print(event.acceleration.x); Serial.print("\t");
  Serial.print("Y: \t"); Serial.print(event.acceleration.y); Serial.print("\t");
  Serial.print("Z: \t"); Serial.print(event.acceleration.z); Serial.print("\t");
  Serial.println("m/s^2 ");*/

  // Read the 'raw' data in 14-bit counts
  mma.read();
  X = mma.x;
  Y = mma.y;
  Z = mma.z;
}


