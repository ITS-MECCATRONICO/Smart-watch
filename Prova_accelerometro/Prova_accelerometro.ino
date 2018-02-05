
int cont = 0;
void setup() 
{

  Serial.begin(9600);

  interruptSetup();

}

void loop() 
{
 
}

ISR(TIMER2_COMPA_vect)
{
  cli(); 
  cont++;

  if(cont == 500)
  {
    Serial.println(micros());
    cont = 0;
  }
  sei();
}// end isr

void interruptSetup()
{
    // Initializes Timer2 to throw an interrupt every 2mS.
    TCCR2A = 0x02;     // DISABLE PWM ON DIGITAL PINS 3 AND 11, AND GO INTO CTC MODE
    TCCR2B = 0x05;     // DON'T FORCE COMPARE, 128 PRESCALER
    OCR2A = 0X7C;      // SET THE TOP OF THE COUNT TO 124 FOR 500Hz SAMPLE RATE
    TIMSK2 = 0x02;     // ENABLE INTERRUPT ON MATCH BETWEEN TIMER2 AND OCR2A
    sei();             // MAKE SURE GLOBAL INTERRUPTS ARE ENABLED
 }
