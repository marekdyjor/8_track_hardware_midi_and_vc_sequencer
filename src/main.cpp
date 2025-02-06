//**************************************************************************************************
//**************************************************************************************************
//*     
//*
//*     8  track sequencer
//*
//*
//**************************************************************************************************
//**************************************************************************************************

//****************************  includes
#include <Arduino.h>
#include <Midi functions.h>
#include <Interrupts.h>
#include <MCP23017.h>
#include <Keyboard.h>
#include <LEDs.h>
#include <Encoders.h>

//****************************  debuging definitions 
#define MIDION
#define MIDIDEBUG
#define CONTROLLDEBUG
#define DEBUGTIMING
long debugTimer1, debugTimer2, debugTimer3, debugTimer4;
#define DEBUGKEYBOARD


//****************************  encoder
long  encoderScanTime   = 0;
const byte encSeqPins[8][2] = {{0, 1},{2, 3},{4, 5},{6, 7},{8, 9},{10, 11},{12, 13},{14, 15}};
const byte encTmpPins[2]    = {1, 2};

//**************************************************************************************************
//****************************  Setup
void setup() {
  // setup serial speed for hairless midi
  Serial.begin(115000); // 
  Serial.println("START");
  //noInterrupts();
  
  pinMode(KEYCOL1 , INPUT_PULLUP);
  pinMode(KEYCOL2 , INPUT_PULLUP);
  pinMode(ROW1 , OUTPUT);
  digitalWrite(ROW1 , HIGH);
  pinMode(ROW2 , OUTPUT);
  digitalWrite(ROW2 , HIGH);
  pinMode(LEDCOL1 , OUTPUT);
  digitalWrite(LEDCOL1 , LOW);
  pinMode(LEDCOL2 , OUTPUT);
  digitalWrite(LEDCOL2 , LOW);
  
  encoderInit();

  // start timer
  beginTimer(pulsePerSec);

  //interrupts();  
}


//**************************************************************************************************
//****************************  Main Loop  :)
void loop() {

//**************************** play notes
  #ifdef DEBUGTIMING
    debugTimer1 = micros();
  #endif
  seqHandler();
  #ifdef DEBUGTIMING
    debugTimer1-= micros();
    Serial.print("                              time of seq ");
    Serial.println(-debugTimer1);
  #endif

//**************************** scan ENCODERs
  #ifdef DEBUGTIMING
    debugTimer4= micros();
  #endif
  if(millis() - encoderScanTime >= 1){
    encoderHandler();
  }
  #ifdef DEBUGTIMING
    debugTimer4-= micros();
    Serial.print("                              time of encoder ");
    Serial.println(-debugTimer4);
  #endif

//**************************** scan LEDs
  #ifdef DEBUGTIMING
    debugTimer2= micros();
  #endif
  ledHandler();
  #ifdef DEBUGTIMING
    debugTimer2-= micros();
    Serial.print("                              time of led ");
    Serial.println(-debugTimer2);
  #endif

//**************************** scan Keys
  #ifdef DEBUGTIMING
    debugTimer3 = micros();
  #endif
  keyboard();
  #ifdef DEBUGTIMING
    debugTimer3-= micros();
    Serial.print("                              time of key ");
    Serial.println(-debugTimer3);
  #endif
}