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
#include <Sequencer.h> 

byte sequence[4][8][3] = {{{60,127,3},{72,64,3},{60,127,7},{72,64,0},{5,127,7},{89,127,3},{12,127,3},{54,127,3}},                    // depreciated
                          {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
                          {{5,127,1},{89,127,1},{12,127,1},{54,127,1},{72,64,1},{60,127,1},{72,64,1},{72,64,1}},
                          {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}}};
int seqLen = 8;
int seqTracks = 1;
int seqPos = 0;
volatile int noteLen = 0;
volatile bool seqRun = false;
volatile bool note1on = false, note1off = false, 
              note2on = false, note2off = false, 
              note3on = false, note3off = false,               
              note4on = false, note4off = false, 
              note6on = false, note6off = false, 
              note8on = false, note8off = false,
              note12on = false, note12off = false,               
              note16on = false, note16off = false;
float tempo = 30.0;
int pulsePerSec = tempo /60 * NOTE01_P;
volatile int pulseCounter = 0;

volatile bool notes[9] = {false, false, false, false, false, false, false, false, false, };
