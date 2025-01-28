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
