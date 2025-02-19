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
extern byte keyledRows[8][2];
extern byte keyCols[8][2];
extern byte ledCols[3][2];      // columns
                    // {port, pin}  port - 0:UNO  1:PORT0A, 2:PORT0B  3:PORT1A, 4:PORT1B  pin - 0-7
                    
//****************************  function definition
extern void encoderInit();
extern void encoderHandler();
//**************************************************************************************************