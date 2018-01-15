int q;
int BPM_temp;

void Save_BPM(){

  BPM_temp = BPM_temp + pulseSensor.getBeatsPerMinute();
  q++;


  if(q == 30){
    BPM_record[B] = BPM_temp / 30;
    ble.print("BPM ");
    ble.println(BPM_record[B]);
    B++;
    q = 0;
    BPM_temp = 0;
  }
}
