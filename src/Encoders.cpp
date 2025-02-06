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
#include <Encoders.h>

//****************************  declarations
int encoderPins[9][3] = {   {0, 0, 1}, {0, 2, 3}, {0, 4, 5}, {0, 6, 7},
                            {1, 0, 1}, {1, 2, 3}, {1, 4, 5}, {1, 6, 7}, {2, 2, 3}};
                            //    {port, pinA, pinB}  port - 0:PORTA, 1:PORTB, 2:UNO  pin - 0-7
                            //    {port, pinA, pinB}  port - 0:UNO    1:PORT0A, 2:PORT0B  pin - 0-7
int encoderValue[9] = {0, 0, 0, 0, 0, 0, 0, 0, 120};
int encoderValueBounds[9][2] = {{0,127},{0,127},{0,127},{0,127},{0,127},{0,127},{0,127},{0,127},{10,240}};        //   {min, max}
int lastClkState[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int clkState[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int dtState[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

//****************************  function definition

//****************************  initialize encoders
void encoderInit(){
    Wire.begin();
    MCP20.Init();
    for(int i=0; i<8; i++){
        MCP20.setPinMode(encoderPins[i][1], encoderPins[i][0] == 0 ? A : B, INPUT_PULLUP);
        MCP20.setPinMode(encoderPins[i][2], encoderPins[i][0] == 0 ? A : B, INPUT_PULLUP);
    }
    pinMode(encoderPins[8][1], INPUT_PULLUP);
    pinMode(encoderPins[8][2], INPUT_PULLUP);
}

//**************************************************************************************************
//****************************  handle encoders
void encoderHandler(){
    for(int i=0; i<9; i++){
        if(i == 8){
            clkState[i] = digitalRead(encoderPins[i][1]);
            dtState[i] = digitalRead(encoderPins[i][2]);
        }else{
            clkState[i] = MCP20.getPin(encoderPins[i][1], encoderPins[i][0] == 0 ? A : B);
            dtState[i] = MCP20.getPin(encoderPins[i][2], encoderPins[i][0] == 0 ? A : B);
        }
        if (clkState[i] != lastClkState[i] && clkState[i] == LOW) {
            if (dtState[i] != clkState[i]) {
                if(encoderValue[i] < encoderValueBounds[i][1]){
                    encoderValue[i]++;
                }
            } else {
                if(encoderValue[i] > encoderValueBounds[i][0]){
                    encoderValue[i]--;
                }
            }
        }
        lastClkState[i] = clkState[i];
    }
}
//**************************************************************************************************