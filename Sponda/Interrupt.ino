
/*void interrupt_setup()
{
  EICRA = 0b00000001; //interrupt su change int0
  EIMSK = 0b00000001; //abilito interrupt int0
  sei();
}

ISR(INT0_vect) //PIN 2 EMERGENZA
{
  cli();

  if (digitalRead(EMERGENZA) == 0)
  {
    digitalWrite(R_D, LOW);
    digitalWrite(R_C, LOW);

    Serial.print("interrupt emergenza LOW");
  
    lampeggia = 1;
  }
  else
  { 
    lampeggia = 0;

    Serial.print("interrupt emergenza HIGH");
    
    digitalWrite(R_D, HIGH);
    digitalWrite(R_LED, LOW);
  }
  
  sei();
}

/*ISR(INT1_vect) //PIN 3 GIU
{
  cli();

  
  
  sei();
}*/

