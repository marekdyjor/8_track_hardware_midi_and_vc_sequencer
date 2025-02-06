//**************************************************************************************************
//**************************************************************************************************
//*
//*         keyboard handling
//*         
//*
//*
//**************************************************************************************************
//**************************************************************************************************

//****************************  includes
#include <Arduino.h>
#include <LEDs.h>
#include <interrupts.h>
#include <Encoders.h>  

#define KEY_TRACK_1 0
#define KEY_TRACK_2 1
#define KEY_TRACK_3 2
#define KEY_TRACK_4 3
#define KEY_TRACK_5 4
#define KEY_TRACK_6 5
#define KEY_TRACK_7 6
#define KEY_TRACK_8 7

#define KEY_NOTE         8
#define KEY_VELOCITY     9
#define KEY_CHORD       10
#define KEY_MODULATION  11
#define KEY_PITCHBEND   12
#define KEY_LENGTH      13
#define KEY_CC1         14
#define KEY_CC2         15

#define KEY_SHIFT1      16
#define KEY_SHIFT2      17
#define KEY_SHIFT3      18
#define KEY_SHIFT4      19
#define KEY_MOVE_LEFT   20
#define KEY_MOVE_RIGHT  21
#define KEY_MENU_1      22
#define KEY_MENU_2      23







//****************************  declarations
extern byte keyledRows[8][2];
extern byte keyCols[8][2];
extern byte keys[8][8][2];   

extern byte  keysDepr[2][2];                    // rows   columns
extern long  keyScanTime;
extern int keyScanInterval;
extern int keyDebounceShort;
extern int keyDebounceLong;


// to be deleted
#define KEY_RUN_STOP i == 1 and j == 1
#define KEY_TEMPO_UP i == 1 and j == 0
#define KEY_TEMPO_DOWN i == 0 and j == 1

#define ROW1 2
#define ROW2 3
#define KEYCOL1 6
#define KEYCOL2 7
#define LEDCOL1 4
#define LEDCOL2 5


//****************************  function definition
extern void keyboard();
extern void setKeyRow(int, int);
extern int readKey(int);