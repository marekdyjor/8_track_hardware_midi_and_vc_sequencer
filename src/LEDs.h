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


//****************************  declarations
extern bool leds[2][2];     // rows   columns

extern long ledScanTime,    //start scan time counter millisecounds
            ledDelayTimer;  // start delay time micro secounds

#define LED_RUN_STOP 1][0
#define LED_MEASUREPULSE 0][0

#define ROW1 2
#define ROW2 3
#define LEDCOL1 4
#define LEDCOL2 5
//****************************  function definition
extern void ledHandler();