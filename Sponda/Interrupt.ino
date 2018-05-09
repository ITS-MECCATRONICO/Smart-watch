
void interrupt_setup()
{
  EICRA = 0b00000101; //interrupt su change int1 & int0
  EIMSK = 0b00000011; //abilito interrupt int1 & int0
  sei();
}

ISR(INT0_vect) //PIN 2 EMERGENZA
{
  cli();

  if (digitalRead(EMERGENZA) == 0)
  {
    digitalWrite(R_D, LOW);
    digitalWrite(R_C, LOW);
  
    lampeggia = 1;
  }
  else
  { 
    lampeggia = 0;
    digitalWrite(R_D, HIGH);
    digitalWrite(R_LED, LOW);
  }
  
  sei();
}

ISR(INT1_vect) //PIN 3 GIU
{
  cli();

  if (digitalRead(GIU) == 0 && digitalRead(FC_DW_SX) == 1 && digitalRead(FC_DW_DX) == 1)//se si può abbassare
  {
    digitalWrite(R_C, LOW);

    if (digitalRead(R_A) == 1 || digitalRead(R_B) == 1)
    {
      commuta_AB = 1;
    }
    
    abbassa_sponda = 1;
  }
  
  sei();
}

