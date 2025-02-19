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
#include <encoders.h>

//****************************  declarations
extern byte leds[8][3][2];        // rows   columns  {controll (0-off, 1-blink, 2-on), number}
extern bool ledsdepr[2][2];     // rows   columns

extern long ledScanTime,    //start scan time counter millisecounds
            ledDelayTimer;  // start delay time micro secounds

#define LED_TRACK_1 0
#define LED_TRACK_2 3
#define LED_TRACK_3 6
#define LED_TRACK_4 9
#define LED_TRACK_5 12
#define LED_TRACK_6 15
#define LED_TRACK_7 18
#define LED_TRACK_8 21

#define KEY_NOTE         1
#define KEY_VELOCITY     4
#define KEY_CHORD        7
#define KEY_MODULATION  10
#define KEY_PITCHBEND   13
#define KEY_LENGTH      16
#define KEY_CC1         19
#define KEY_CC2         22

#define LED_SHIFT1      2
#define LED_SHIFT2      5
#define LED_SHIFT3      8
#define LED_SHIFT4     11
#define LED_TEMPO      14


//****************************  function definition
extern void ledHandler();
extern void setLed(int,int);
extern void setLedRow(int, int);
extern void setLedCol(int, int);