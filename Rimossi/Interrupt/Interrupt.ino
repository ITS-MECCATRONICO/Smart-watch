
void interruptSetup(){
  
  // Initializes Timer2 to throw an interrupt every 2mS.
  TCCR2A = 0x02;     // DISABLE PWM ON DIGITAL PINS 3 AND 11, AND GO INTO CTC MODE
  TCCR2B = 0x05;     // DON'T FORCE COMPARE, 128 PRESCALER
  OCR2A = 0X7C;      // SET THE TOP OF THE COUNT TO 124 FOR 500Hz SAMPLE RATE
  TIMSK2 = 0x02;     // ENABLE INTERRUPT ON MATCH BETWEEN TIMER2 AND OCR2A
  sei();             // MAKE SURE GLOBAL INTERRUPTS ARE ENABLED
}
       /* // Initializes Timer1 to throw an interrupt every 2mS.
        TCCR1A = 0x00; // DISABLE OUTPUTS AND PWM ON DIGITAL PINS 9 & 10
        TCCR1B = 0b00001101; // CTC, PRE 1024
        TCCR1C = 0x00; // DON'T FORCE COMPARE
        OCR1A = 0xFF; // 255
        TIMSK1 = 0x02; // ENABLE INTERRUPT ON MATCH BETWEEN TIMER1 AND OCR2A

        // TIMER 2 IMPULSO OGNI 0.02s 50Hz (0.19968s)
        TCCR2A = 0x02;     // DISABLE PWM ON DIGITAL PINS 3 AND 11, AND GO INTO CTC MODE
        TCCR2B = 0x07;     // DON'T FORCE COMPARE, 1024 PRESCALER
        OCR2A = 0X4D;      // 77
        TIMSK2 = 0x02;     // ENABLE INTERRUPT ON MATCH BETWEEN TIMER2 AND OCR2A  
        
        sei();         // enable GLOBAL INTERRUPTS
      }*/

// THIS IS THE TIMER 2 INTERRUPT SERVICE ROUTINE.
// Timer 2 makes sure that we take a reading every 2 miliseconds
ISR(TIMER2_COMPA_vect){                         
  pulse_sensor();
}// end isr

