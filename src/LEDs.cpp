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
#include <LEDs.h>

//****************************  declarations
byte leds[8][3][2]        ={{{0, 0},{0, 1},{0, 2}},
                            {{0, 3},{0, 4},{0, 5}},
                            {{0, 6},{0, 7},{0, 8}},
                            {{0, 9},{0,10},{0,11}},
                            {{0,12},{0,13},{0,14}},
                            {{0,15},{0,16},{0,17}},
                            {{0,18},{0,19},{0,20}},
                            {{0,21},{0,22},{0,23}}};
                            // rows   columns  {controll (0-off, 1-blink, 2-on), number}
bool ledsdepr[2][2] = {{false, false},{false, false}};    // rows   columns

long  ledScanTime       = 0,      //start scan time counter millisecounds
      ledDelayTimer     = 0;      // start delay time micro secounds

//****************************  function definition
void ledHandler() {
  for(int i=0; i<2; i++)  {   //led columns
    setLedCol(i,HIGH);
    for(int j=0; j<2; j++)  {                 // led rows
      if(leds[i][j][2] == 2){
        setLedRow(j, LOW);
        ledDelayTimer = micros();
        while (micros() - ledDelayTimer < 1) {}   //delay  1us
      }
      setLedRow(j, HIGH);      
      ledDelayTimer = micros();
      while (micros() - ledDelayTimer < 2) {}     //delay  2us
    }
    setLedCol(i, LOW);
  }
}   

//****************************  set led column
void setLedCol(int i, int state){
  switch (ledCols[i][0]){
  case 0:
    digitalWrite(ledCols[i][1],state);
    break;
  case 1:
    MCP20.setPin(ledCols[i][1], A,state);
    break;
  case 2:
    MCP20.setPin(ledCols[i][1], B,state);
    break;
  case 3:
    MCP20.setPin(ledCols[i][1], A,state);
    break;
  case 4:
    MCP21.setPin(ledCols[i][1], B,state);
    break;
  default:
    break;
  }
}

//****************************  set led row
void setLedRow(int i, int state){
  switch (keyledRows[i][0]){
  case 0:
    digitalWrite(keyledRows[i][1],state);
    break;
  case 1:
    MCP20.setPin(keyledRows[i][1], A, state);
    break;
  case 2:
    MCP20.setPin(keyledRows[i][1], B, state);
    break;
  case 3:
    MCP20.setPin(keyledRows[i][1], A, state);
    break;
  case 4:
    MCP21.setPin(keyledRows[i][1], B, state);
    break;
  default:
    break;
  }
}


//****************************  set led
void setLed(int i, int j){     // i - led number, j - led state
  int k = 0, l = 0;       // k - row, l - column
  while(k<8){
    while(l<3){
      if(leds[k][l][1] == i){
        leds[k][l][0] = j;
        return;
      }
      l++;
    }
    l=0;
    k++;
  }
}