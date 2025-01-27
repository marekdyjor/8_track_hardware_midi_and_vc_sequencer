//**************************************************************************************************
//**************************************************************************************************
//*
//*         Sequencer data structures and functions
//*         Storing and Retriving data on SD card
//*
//*
//**************************************************************************************************
//**************************************************************************************************

//****************************  includes
#include <Arduino.h>

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
int seqLen1 = 4;
int seqPos1 = 0;
int noteLen1 = 8;
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
