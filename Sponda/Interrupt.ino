
ISR(TIMER2_COMPA_vect)
{
  cli();

  //Serial.println("ACCELEROMETRO");
  Take_MMA8451();
  
  sei();
}// end int_1

void Timer_1_Setup() //ISR(TIMER1_OVF_vect)
{
  // Initializes Timer1 to throw an interrupt every 2mS.
  TCCR1A = 0x00; // DISABLE OUTPUTS AND PWM ON DIGITAL PINS 9 & 10
  TCCR1B = 0x11; // GO INTO 'PHASE AND FREQUENCY CORRECT' MODE, NO PRESCALER
  TCCR1C = 0x00; // DON'T FORCE COMPARE
  TIMSK1 = 0x01; // ENABLE OVERFLOW INTERRUPT (TOIE1)
  ICR1 = 8000;  // TRIGGER TIMER INTERRUPT EVERY 2mS
  sei();         // MAKE SURE GLOBAL INTERRUPTS ARE ENABLED
}

void Timer_2_Setup() //ISR(TIMER2_COMPA_vect)
{ 
  // Initializes Timer2 to throw an interrupt every 2mS.
  TCCR2A = 0x02;     // DISABLE PWM ON DIGITAL PINS 3 AND 11, AND GO INTO CTC MODE
  TCCR2B = 0x05;     // DON'T FORCE COMPARE, 128 PRESCALER
  OCR2A = 0X7C;      // SET THE TOP OF THE COUNT TO 124 FOR 500Hz SAMPLE RATE
  TIMSK2 = 0x02;     // ENABLE INTERRUPT ON MATCH BETWEEN TIMER2 AND OCR2A
  sei();             // MAKE SURE GLOBAL INTERRUPTS ARE ENABLED
}

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

