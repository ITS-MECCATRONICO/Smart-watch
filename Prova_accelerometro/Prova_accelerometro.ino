void setup() 
{

  TCCR2A = 0x02;          // Disable PWM and go into CTC mode
  TCCR2B = 0x05;          // don't force compare, 128 prescaler
  OCR2A = 0X7C;           // set count to 124 for 2mS interrupt
  TIMSK2 = 0x02;          // Enable OCR2A match interrupt

}

void loop() {
  // put your main code here, to run repeatedly:

}


