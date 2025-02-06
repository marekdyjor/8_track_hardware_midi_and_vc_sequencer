//**************************************************************************************************
//**************************************************************************************************
//*
//*         encoders handling
//*         
//*
//*
//**************************************************************************************************
//**************************************************************************************************

//****************************  includes
#include <Arduino.h>
#include <Expanders.h>

//****************************  declarations
extern int encoderPins[9][3];               //    {port, pinClk, pinDt}  port - 0:PORTD, 1:PORTB, 2:UNO  pin - 0-7
extern int encoderValue[9]; 
extern int encoderValueBounds[9][2];        //   {min, max}
extern int lastClkState[9];
extern int clkState[9];
extern int dtState[9];


//****************************  function definition
extern void encoderInit();
extern void encoderHandler();
//**************************************************************************************************