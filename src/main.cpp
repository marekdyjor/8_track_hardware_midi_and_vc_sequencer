//**************************************************************************************************
//**************************************************************************************************
//*     8  track sequencer
//*     
//*
//*
//*
//**************************************************************************************************
//**************************************************************************************************


//****************************  includes
#include <Arduino.h>
#include <Midi functions.h>
#include <Interrupts.h>
#include <MCP23017.h>

//****************************  debuging definitions 
#define MIDION
#define MIDIDEBUG
#define CONTROLLDEBUG
#define DEBUGTIMING
long debugTimer1, debugTimer2, debugTimer3, debugTimer4;
#define DEBUGKEYBOARD

//****************************  keyboard and LED
bool leds[2][2] = {{false, false},{false, false}};    // rows   columns
int  keys[2][2] = {{0, 0},{0, 0}};                    // rows   columns

long  keyScanTime       = 0,
      ledScanTime       = 0,      //start scan time counter millisecounds
      ledDelayTimer     = 0;      // start delay time micro secounds

#define LED_RUN_STOP 1][0
#define LED_MEASUREPULSE 0][0
#define KEY_RUN_STOP i == 1 and j == 1
#define KEY_TEMPO_UP i == 1 and j == 0
#define KEY_TEMPO_DOWN i == 0 and j == 1

#define ROW1 2
#define ROW2 3
#define KEYCOL1 6
#define KEYCOL2 7
#define LEDCOL1 4
#define LEDCOL2 5

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
  if(seqRun){
    if(note4on and note4off){
      // Send a "Note On" message
      #ifdef MIDIDEBUG
        Serial.print(pulseCounter);
        Serial.print("  note on  ");
        Serial.print(sequence[0][seqPos][0]);      
        Serial.print(" velocity ");
        Serial.print(sequence[0][seqPos][1]);      
        Serial.print(" time ");
        Serial.println(sequence[0][seqPos][2]);      
      #endif
      #ifdef MIDION
        for(int k=0; k<seqTracks; k++){
          SendNoteOn(0, k, sequence[k][seqPos][0], sequence[k][seqPos][1]);
          noteLen=sequence[k][seqPos][2];
        }
      #endif      
      note4off = true;
      seqPos++;
      if(seqLen == seqPos){seqPos = 0;}
    }
    
    if(not note4on and note4off){
      #ifdef MIDIDEBUG
        Serial.print(pulseCounter);
        Serial.println("  note off");
      #endif
      #ifdef MIDION
        for(int k=0; k<4; k++){
          SendNoteOff(0, k, sequence[k][seqPos][0], 0x00);
        }      
      #endif
      note4off = false;
    }    
  }
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
  //if(micros() - ledScanTime > 10){
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
  //  ledScanTime = micros();
  //}
  #ifdef DEBUGTIMING
    debugTimer2-= micros();
    Serial.print("                              time of led ");
    Serial.println(-debugTimer2);
  #endif

//**************************** scan Keys
  #ifdef DEBUGTIMING
    debugTimer3 = micros();
  #endif
  
  if(millis() - keyScanTime > 10){
    for(int i=0; i<2; i++)  {   //key rows
      digitalWrite(ROW1+i,LOW);    
      for(int j=0; j<2; j++)  {                 // key columns
        if(digitalRead(KEYCOL1+j) == LOW){      //  LOW it means key is pressed
          if(keys[i][j] <50){keys[i][j]++;}
          #ifdef DEBUGKEYBOARD            
            Serial.print("------------------------key i ");
            Serial.print(i);
            Serial.print(" j ");
            Serial.print(j);
            Serial.print(" key state ");            
            Serial.println(keys[i][j]);
          #endif                      
          if(keys[i][j] == 5){                                //short press
            if (KEY_RUN_STOP){                           // RUN / STOP toggle
              //keys[i][j] = 5;
              seqRun = not seqRun;
              leds[LED_RUN_STOP] = seqRun;
              #ifdef CONTROLLDEBUG            
                Serial.println(seqRun ? "RUN" : "STOP");  
              #endif            
            }
            if (KEY_TEMPO_UP){                           // tempo UP
              tempo+=1;
              seqPulse.stop();
              seqPulse.set_frequency(tempo /60.0 * 96.0);
              seqPulse.reset();
              seqPulse.start();
              #ifdef CONTROLLDEBUG            
                Serial.print("Tempo  ");
                Serial.println(tempo);
              #endif            
            }
            if (KEY_TEMPO_DOWN){                           // tempo DOWN
              tempo-=1;
              seqPulse.stop();
              seqPulse.set_frequency(tempo /60.0 * 96.0);
              seqPulse.reset();
              seqPulse.start();
              #ifdef CONTROLLDEBUG            
                Serial.print("Tempo  ");
                Serial.println(tempo);
              #endif            
            }
          }
          if(keys[i][j] >= 50){                               //  long press
            if (KEY_TEMPO_UP){                           // tempo UP repetitive
              tempo+=1;
              seqPulse.stop();
              seqPulse.set_frequency(tempo /60.0 * 96.0);
              seqPulse.reset();
              seqPulse.start();
              #ifdef CONTROLLDEBUG            
                Serial.print("Tempo  ");
                Serial.println(tempo);
              #endif            
            }
            if (KEY_TEMPO_DOWN){                           // tempo DOWN   repetitive
              tempo-=1;
              seqPulse.stop();
              seqPulse.set_frequency(tempo /60.0 * 96.0);
              seqPulse.reset();
              seqPulse.start();
              #ifdef CONTROLLDEBUG            
                Serial.print("Tempo  ");
                Serial.println(tempo);
              #endif            
            }
          }
        }else{
          if(keys[i][j] > 0){keys[i][j]--;}
          #ifdef DEBUGKEYBOARD            
            Serial.print("------------------------key i ");
            Serial.print(i);
            Serial.print(" j ");
            Serial.print(j);
            Serial.print(" key state ");            
            Serial.println(keys[i][j]);
          #endif                      
        }
      }
      digitalWrite(ROW1+i,HIGH);
    }
    keyScanTime = millis();
  }
  #ifdef DEBUGTIMING
    debugTimer3-= micros();
    Serial.print("                              time of key ");
    Serial.println(-debugTimer3);
  #endif
}