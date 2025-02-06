//**************************************************************************************************
//**************************************************************************************************
//*
//*         LEDs handling
//*         
//*
//*
//**************************************************************************************************
//**************************************************************************************************

//****************************  includes
#include <Arduino.h>
#include <LEDs.h>

bool leds[2][2] = {{false, false},{false, false}};    // rows   columns

long  ledScanTime       = 0,      //start scan time counter millisecounds
      ledDelayTimer     = 0;      // start delay time micro secounds

#define LED_RUN_STOP 1][0
#define LED_MEASUREPULSE 0][0

//****************************  function definition
void ledHandler() {
    for(int i=0; i<2; i++)  {   //led columns
    
    digitalWrite(LEDCOL1+i,HIGH);
    for(int j=0; j<2; j++)  {                 // key and led rows
      
      if(leds[j][i]){
        digitalWrite(ROW1+j,LOW);   
        ledDelayTimer = micros();
        while (micros() - ledDelayTimer < 1) {}   //delay  1us
      }
      digitalWrite(ROW1+j,HIGH);   
      ledDelayTimer = micros();
      while (micros() - ledDelayTimer < 2) {}     //delay  2us
    }
    digitalWrite(LEDCOL1+i,LOW);
  }
}   