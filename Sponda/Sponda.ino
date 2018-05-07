//-------------------Relè---------------------------
int R_A = 8;
int R_B = 6;
int R_C = 4;
int R_D = 9;
int R_LED = 5;
//-------------------Pulsantiera---------------------
int EMERGENZA = 2;//NC 5V
int SU = 7;//NC 5V
int GIU = 3;//NC 5V
//-------------------Finecorsa------------------------
int FC_UP_SX = 10;//NA GND
int FC_DW_SX = 11;//NA GND
int FC_UP_DX = 12;//NA GND
int FC_DW_DX = 13;//NA GND

bool lampeggia, led_state = 0, alza_sponda = 0, abbassa_sponda = 0, commuta_AB;


long this_time, last_time;

void setup() 
{
  Serial.begin(9600);
//-------------------Relè---------------------------
  pinMode(R_A, OUTPUT);
  pinMode(R_B, OUTPUT);
  pinMode(R_C, OUTPUT);
  pinMode(R_D, OUTPUT);
  pinMode(R_LED, OUTPUT);
//-------------------Pulsantiera---------------------
  pinMode(EMERGENZA, INPUT);
  pinMode(SU, INPUT);
  pinMode(GIU, INPUT);
//-------------------Finecorsa------------------------
  pinMode(FC_UP_SX, INPUT_PULLUP);
  pinMode(FC_UP_SX, INPUT_PULLUP);
  pinMode(FC_UP_SX, INPUT_PULLUP);
  pinMode(FC_UP_SX, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(EMERGENZA), Emergenza, CHANGE);
  attachInterrupt(digitalPinToInterrupt(GIU), Abbassa, LOW);

  this_time = millis();
}

void loop() 
{
//--------------------------lampeggia led se emergenza-------------------------
  if (lampeggia == 1)
  {
    if (this_time - last_time >= 2000)
    {
      led_state != led_state;
      last_time = this_time;
    }
    digitalWrite(R_LED, led_state);
  }

//---------------------------abbassa sponda-------------------------------------
  if (abbassa_sponda == 1) 
  {
    if (commuta_AB == 1)
    {
      delay (50);
      digitalWrite(R_A, HIGH);
      digitalWrite(R_B, HIGH);

      commuta_AB = 0;
    }
    
    delay (50);

    while(GIU == 0 && FC_DW_SX == 0 && FC_DW_DX == 0)//finchè premuto e no finecorsa
    {
      digitalWrite(R_C, HIGH);
      digitalWrite(R_LED, HIGH);
    }

    digitalWrite(R_C, LOW);
    digitalWrite(R_LED, LOW);
    abbassa_sponda = 0;
  }

//------------------------------alza sponda-------------------------------------
  Alza();
  if (alza_sponda == 1)
  {
    if (commuta_AB == 1)
    {
      delay (50);
      digitalWrite(R_A, LOW);
      digitalWrite(R_B, LOW);

      commuta_AB = 0;
    }
    
    delay (50);

    while(SU == 0 && FC_UP_SX == 0 && FC_UP_DX == 0)//finchè premuto e no finecorsa
    {
      digitalWrite(R_C, HIGH);
      digitalWrite(R_LED, HIGH);
    }

    digitalWrite(R_C, LOW);
    digitalWrite(R_LED, LOW);
    alza_sponda = 0;
  }
}

//--------------------------routine di interrupt emergenza-------------------------
void Emergenza()
{
  if (EMERGENZA == 1)
  {
    digitalWrite(R_C, LOW);
    digitalWrite(R_D, LOW);
  
    lampeggia = 1;
  }
  else
  {
    digitalWrite(R_D, HIGH);
    
    lampeggia = 0;
    digitalWrite(R_LED, LOW);
  }
}

//--------------------------routine di interrupt abbassa sponda-----------------------
void Abbassa()
{
  if (GIU == 0 && FC_DW_SX == 0 && FC_DW_DX == 0)//se si può abbassare
  {
    digitalWrite(R_C, LOW);

    if (R_A == 0 || R_B == 0)
    {
      commuta_AB = 1;
    }
    
    abbassa_sponda = 1;
  }
}

//--------------------------routine alza sponda-----------------------
void Alza()
{
  if (SU == 0 && FC_UP_SX == 0 && FC_UP_DX == 0)//se si può alzare
  {
    digitalWrite(R_C, LOW);

    if (R_A == 1 || R_B == 1)
    {
      commuta_AB = 1;
    }
    alza_sponda = 1;
  }
}

