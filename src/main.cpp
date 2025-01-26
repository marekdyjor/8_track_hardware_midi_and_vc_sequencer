//****************************  includes
#include <Arduino.h>
#include <FspTimer.h>
//#include <MCP23017.h>
//#include <MIDI.h>

//****************************  debuging definitions 
//#define MIDION
#define MIDIDEBUG
//#define CONTROLLDEBUG
//#define DEBUGTIMING
long debugTimer1, debugTimer2, debugTimer3, debugTimer4;
//#define DEBUGKEYBOARD

//****************************  create timer object
FspTimer seqPulse;

//****************************  port definitions
#define ROW1 2
#define ROW2 3

#define KEYCOL1 6
#define KEYCOL2 7

#define LEDCOL1 4
#define LEDCOL2 5

//****************************  keyboard and LED
bool leds[2][2] = {{false, false},{false, false}};    // rows   columns
int  keys[2][2] = {{0, 0},{0, 0}};                    // rows   columns

long  startScanTime     = 0,
      startLEDScanTime  = 0;      //start scan time counter millisecounds
long startTime          = 0;      // start delay time micro secounds

#define LED_RUN_STOP 1][0
#define LED_MEASUREPULSE 0][0
#define KEY_RUN_STOP i == 1 and j == 1
#define KEY_TEMPO_UP i == 1 and j == 0
#define KEY_TEMPO_DOWN i == 0 and j == 1

//****************************  Sequencer data
struct seqTrackDesc {
  int trackID     = 0;
  byte seqLen     = 16;
  byte noteLenght = 0;
  int  noteTime   = 0;  // ms
  String name     = "";
  bool protectedTrack  = false;
  bool savedToSDTrack  = false;
};

struct seqTrackPos {
  int noteTime    = 0;  //  ms
  byte note       = 0;
  byte velocity   = 0;
  byte chord      = 0;
  byte modulation = 0;
  int pitchBend   = 0;
  byte CC1        = 0;
  byte CC1Value   = 0;
  byte CC2        = 0;
  byte CC2Value   = 0;
};

struct TrackDesc {
  byte Port       = 0;
  byte chanell    = 0;
  byte seqPos     = 0;
  byte scale      = 0;
  int transpoze   = 0;
  byte transMIDIPort      = 0;
  byte transMIDIChanell   = 0;
  byte transMIDIBaseNote  = 0;  
  seqTrackDesc trackDesc;
  seqTrackPos sequence[32];
};

TrackDesc seqences[8];

byte sequence[4][4][2] = {{{60,127},{72,64},{60,127},{72,64}},                    // depreciated
                          {{0,0},{0,0},{0,0},{0,0}},
                          {{5,127},{89,127},{12,127},{54,127}},
                          {{0,0},{0,0},{0,0},{0,0}}};
int seqLen = 4;
int seqPos = 0;
int noteLen = 8;
volatile bool seqRun = false;
volatile bool note_4on = false, note_4off = false,
              note_2on = false, note_2off = false,
              note1on = false, note1off = false, 
              note2on = false, note2off = false, 
              note4on = false, note4off = false, 
              note8on = false, note8off = false,
              note16on = false, note16off = false;
float tempo = 30.0;
int pulsePerSec = tempo /60 * 96; // 192
volatile int pulseCounter = 0;

volatile bool notes[9] = {false, false, false, false, false, false, false, false, false, };

#define NOTE01_P 192
#define NOTE02_P  96
#define NOTE03_P  64
#define NOTE04_P  48
#define NOTE06_P  32
#define NOTE08_P  24
#define NOTE12_P  16
#define NOTE16_P  12
#define NOTE24_P   8

//**************************************************************************************************
//****************************  function Declarations
//int myFunction(int, int);
void timer_callback(timer_callback_args_t *p_args);
bool beginTimer(float);
void SendNoteOn(byte, byte, byte, byte);
void SendNoteOff(byte, byte, byte, byte); 


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
    if(note4on){
      // Send a "Note On" message
      #ifdef MIDIDEBUG
        Serial.print(pulseCounter);
        Serial.print("  note on  ");
        Serial.print(sequence[0][seqPos][0]);      
        Serial.println(sequence[0][seqPos][1]);      
      #endif
      #ifdef MIDION
        for(int k=0; k<4; k++){
          SendNoteOn(0, k, sequence[k][seqPos][0], sequence[k][seqPos][1]);
        }
      #endif      
      note4on = false;
      seqPos++;
      if(seqLen == seqPos){seqPos = 0;}
    }

    if(note4off){
      // Send a "Note Off" message
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

    if(note_4on){
      leds[LED_MEASUREPULSE] = true;
      note_4on = false;
    }
    if(note_4off){
      leds[LED_MEASUREPULSE] = false;
      note_4off = false;
    }    
  }
  #ifdef DEBUGTIMING
    debugTimer1-= micros();
    Serial.print("                              time of seq ");
    Serial.println(debugTimer1);
  #endif

//**************************** scan LEDs
  #ifdef DEBUGTIMING
    debugTimer2= micros();
  #endif
  //if(micros() - startLEDScanTime > 10){
    for(int i=0; i<2; i++)  {   //led columns
      
      digitalWrite(LEDCOL1+i,HIGH);
      for(int j=0; j<2; j++)  {                 // key and led rows
        
        if(leds[j][i]){
          digitalWrite(ROW1+j,LOW);   
          startTime = micros();
          while (micros() - startTime < 1) {}   //delay  1us
        }
        digitalWrite(ROW1+j,HIGH);   
        startTime = micros();
        while (micros() - startTime < 2) {}     //delay  2us
      }
      digitalWrite(LEDCOL1+i,LOW);
    }
  //  startLEDScanTime = micros();
  //}
  #ifdef DEBUGTIMING
    debugTimer2-= micros();
    Serial.print("                              time of led ");
    Serial.println(debugTimer2);
  #endif

//**************************** scan Keys
  #ifdef DEBUGTIMING
    debugTimer3 = micros();
  #endif
  
  if(millis() - startScanTime > 10){
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
    startScanTime = millis();
  }
  #ifdef DEBUGTIMING
    debugTimer3-= micros();
    Serial.print("                              time of key ");
    Serial.println(debugTimer3);
  #endif

}

//**************************************************************************************************
//****************************  interrupt timer callbackMain
void timer_callback(timer_callback_args_t __attribute((unused)) *p_args){
    if(pulseCounter==0){
      note_4on  = true;
      note1on   = true;
      note2on   = true;
      note4on   = true;
      note8on   = true;
      note16on  = true;
    }
      
    if(pulseCounter % 192 == 0 and pulseCounter % 384 == 0 ){
      note_4on = true;
    }
    if(pulseCounter % 192 == 0 and pulseCounter % 384 != 0 ){
      note_4off = true;
    }
       
    if(pulseCounter % 48 == 0 and pulseCounter % 96 == 0 ){
      note1on = true;
    }
    if(pulseCounter % 48 == 0 and pulseCounter % 96 != 0 ){
      note1off = true;
    }
    
    if(pulseCounter % 24 == 0 and pulseCounter % 48 == 0 ){
      note2on = true;
    }
    if(pulseCounter % 24 == 0 and pulseCounter % 48 != 0 ){
      note2off = true;
    }

    if(pulseCounter % 12 == 0 and pulseCounter % 24 == 0 ){
      note4on = true;
    }
    if(pulseCounter % 12 == 0 and pulseCounter % 24 != 0 ){
      note4off = true;
    }

    if(pulseCounter % 48 == 0 and pulseCounter % 96 == 0 ){
      note1on = true;
    }
    if(pulseCounter % 48 == 0 and pulseCounter % 96 != 0 ){
      note1off = true;
    }

    pulseCounter++;
}

//**************************************************************************************************
//****************************  initialize Timer
bool beginTimer(float rate) {
  uint8_t timer_type = GPT_TIMER;
  int8_t tindex;
  tindex = FspTimer::get_available_timer(timer_type);
  if (tindex < 0){
    tindex = FspTimer::get_available_timer(timer_type, true);
  }
  if (tindex < 0){
    return false;
  }

  FspTimer::force_use_of_pwm_reserved_timer();

  if(!seqPulse.begin(TIMER_MODE_PERIODIC, timer_type, tindex, rate, 0.0f, timer_callback)){
    return false;
  }

  if (!seqPulse.setup_overflow_irq()){
    return false;
  }

  if (!seqPulse.open()){
    return false;
  }

  if (!seqPulse.start()){
    return false;
  }
  return true;
}

//**************************************************************************************************
//****************************  SendNoteOn
void SendNoteOn(byte port, byte channel, byte note, byte velocity)  {
  if(port == 0){
    Serial.write((0x90+channel));           // Note On channel 
    Serial.write(byte(note));               // note value
    Serial.write(byte(velocity));           // velocity
  }
  else{
    Serial1.write((0x90+channel));           // Note On channel 1
    Serial1.write(byte(note));               // note value
    Serial1.write(byte(velocity));           // velocity
  }
}

//**************************************************************************************************
//****************************  SendNoteOff
void SendNoteOff(byte port, byte channel, byte note, byte velocity) {
  if(port == 0){
    Serial.write(byte(0x80+channel));       // Note On channel 
    Serial.write(byte(note));               // note value
    Serial.write(byte(velocity));           // velocity
  }
  else{
    Serial1.write((0x80+channel));           // Note On channel 1
    Serial1.write(byte(note));               // note value
    Serial1.write(byte(velocity));           // velocity
  }
}

