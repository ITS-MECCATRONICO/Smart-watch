int q;
int BPM_temp;

void Save_BPM(){

  BPM_temp = BPM_temp + BPM;
  q++;

  if(q == 10){   
    BPM_record[B] = BPM_temp / 10; 
    Serial.println(BPM_record[B]);     
    B++;
    q = 0;
    BPM_temp = 0;
  }
}

