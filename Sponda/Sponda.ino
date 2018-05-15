
#include <MMA8451_n0m1.h>
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

//-----------------Accelerometro---------------------
bool su_X, su_Y, su_Z;//accel
bool giu_X, giu_Y, giu_Z;//accel

int Ax_1[30], Ay_1[30], Az_1[30];
int Ax_2[30], Ay_2[30], Az_2[30];
int index_1, index_2, cont = 1, cont_1_s;
int X, Y, Z;
int PICCO_X, PICCO_Y, PICCO_Z;
int picco_X, picco_Y, picco_Z;
int last_X, last_Y, last_Z;
int last_osc_X, last_osc_Y, last_osc_Z;
int Osc_X, Osc_Y, Osc_Z;
int freq_X, freq_Y, freq_Z;

long tempx, tempy, tempz;

//---------------------Sponda-----------------------
bool lampeggia, led_state = 0, alza_sponda = 0, abbassa_sponda = 0, commuta_AB;
bool su, giu, fc_up_sx, fc_dw_sx, fc_up_dx, fc_dw_dx, emergenza;

int This_ing, Last_ing;

long this_time, last_time, delay_alza, delay_abbassa;

//------------------------------------------------------------------------------------
MMA8451_n0m1 accel;

//------------------------------------------------------------------------------------
void setup() 
{
  Serial.begin(115200);

  Serial.print("Start setup");
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
  pinMode(FC_DW_SX, INPUT_PULLUP);
  pinMode(FC_UP_DX, INPUT_PULLUP);
  pinMode(FC_DW_DX, INPUT_PULLUP);
  
  //attachInterrupt(digitalPinToInterrupt(EMERGENZA), Emergenza, FALLEN);
  //attachInterrupt(digitalPinToInterrupt(GIU), Abbassa, LOW);

  //interrupt_setup();

  Setup_MMA8451();
  Timer_2_Setup();
  
  last_time = millis();
}

void loop() 
{ 
  su = digitalRead(SU);
  giu = digitalRead(GIU);
  fc_up_sx = digitalRead(FC_UP_SX);
  fc_dw_sx = digitalRead(FC_DW_SX);
  fc_up_dx = digitalRead(FC_UP_DX);
  fc_dw_dx = digitalRead(FC_DW_DX);
  emergenza = digitalRead(EMERGENZA);
  
  This_ing = (su + (10 * giu) + (100 * fc_up_sx) + (1000 * fc_dw_sx) + (10000 * fc_up_dx) + (100000 * fc_dw_dx) + (1000000 * emergenza)); 

  if (This_ing != Last_ing)
  {
    Print();
    Last_ing = This_ing;
  }

  Event_MMA8451();

  Emergenza();
  
//--------------------------lampeggia led se emergenza-------------------------
  this_time = millis();
  
  if (lampeggia == 1)
  {
    if (this_time - last_time > 500)
    {
      if (led_state == 0)
      {
        led_state = 1;
      }
      else
      {
        led_state = 0;
      }
      
      digitalWrite(R_LED, led_state);
      last_time = millis();
    } 
  }

//---------------------------abbassa sponda-------------------------------------
  Abbassa();
  Emergenza();
  if (abbassa_sponda == 1) 
  {
    if (commuta_AB == 1)
    {
      delay (50);
      digitalWrite(R_A, LOW);
      digitalWrite(R_B, LOW);

      commuta_AB = 0;
    }
    
    delay (50);

    while(digitalRead(EMERGENZA) == 1 && digitalRead(GIU) == 0 && digitalRead(R_A) == 0 && digitalRead(R_B) == 0 && digitalRead(FC_DW_SX) == 1 && digitalRead(FC_DW_DX) == 1)//finchè premuto e no finecorsa
    {
      digitalWrite(R_C, HIGH);
      digitalWrite(R_LED, HIGH);
      delay(10);//delay anti-rimbalzo ingresso
    }

    digitalWrite(R_C, LOW);
    digitalWrite(R_LED, LOW);
    abbassa_sponda = 0;
    delay_abbassa = millis() + 10000;//timer per evitare invesione anticipata
  }

//------------------------------alza sponda-------------------------------------
  Alza();
  Emergenza();
  if (alza_sponda == 1)
  {
    if (commuta_AB == 1)
    {
      delay (50);
      digitalWrite(R_A, HIGH);
      digitalWrite(R_B, HIGH);

      commuta_AB = 0;
    }
    
    delay (50);

    while(digitalRead(EMERGENZA) == 1 && digitalRead(SU) == 0 && digitalRead(R_A) == 1 && digitalRead(R_B) == 1 && digitalRead(FC_UP_SX) == 1 && digitalRead(FC_UP_DX) == 1)//finchè premuto e no finecorsa
    {
      digitalWrite(R_C, HIGH);
      digitalWrite(R_LED, HIGH);
      delay(10);//delay anti-rimbalzo ingresso
    }

    digitalWrite(R_C, LOW);
    digitalWrite(R_LED, LOW);
    alza_sponda = 0;
    delay_alza = millis() + 10000;//timer per evitare invesione anticipata
  }
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//-----------------------------routine di emergenza--------------------------------
void Emergenza()
{
  if (digitalRead(EMERGENZA) == 0)
  {
    Serial.print("interrupt emergenza LOW");

    digitalWrite(R_D, LOW);
    digitalWrite(R_C, LOW);
  
    lampeggia = 1;
  }
  else
  { 
    lampeggia = 0;

    //Serial.print("interrupt emergenza HIGH");
    
    digitalWrite(R_D, HIGH);
    digitalWrite(R_LED, LOW);
  }
  
}

//--------------------------routine abbassa sponda-----------------------
void Abbassa()
{
  if (digitalRead(EMERGENZA) == 1 && digitalRead(GIU) == 0 && digitalRead(FC_DW_SX) == 1 && digitalRead(FC_DW_DX) == 1)//se si può abbassare
  {
    if (millis() > delay_alza)//timer per evitare invesione anticipata
    {
      Serial.print("ABBASSA");
    
      digitalWrite(R_C, LOW);
  
      if (digitalRead(R_A) == 1 || digitalRead(R_B) == 1)
      {
        commuta_AB = 1;
      }
      abbassa_sponda = 1;
    } 
  }
}

//--------------------------routine alza sponda-----------------------
void Alza()
{ 
  if (digitalRead(EMERGENZA) == 1 && digitalRead(SU) == 0 && digitalRead(FC_UP_SX) == 1 && digitalRead(FC_UP_DX) == 1)//se si può alzare
  {
    if (millis() > delay_abbassa)//timer per evitare invesione anticipata
    {
      Serial.print("ALZA");
    
      digitalWrite(R_C, LOW);
  
      if (digitalRead(R_A) == 0 || digitalRead(R_B) == 0)
      {
        commuta_AB = 1;
      }
      alza_sponda = 1;
    } 
  }
}

void Print()
{
  Serial.println("---------------------------------------------------------");
  Serial.print("su");
  Serial.println(su);
  Serial.print("giu");
  Serial.println(giu);
  Serial.print("fc_up_sx");
  Serial.println(fc_up_sx);
  Serial.print("fc_dw_sx");
  Serial.println(fc_dw_sx);
  Serial.print("fc_up_dx");
  Serial.println(fc_up_dx);
  Serial.print("fc_dw_dx");
  Serial.println(fc_dw_dx);
  Serial.print("emergenza");
  Serial.println(emergenza);
  Serial.println("---------------------------------------------------------");
}

