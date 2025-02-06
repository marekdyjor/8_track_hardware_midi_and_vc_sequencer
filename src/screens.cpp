//**************************************************************************************************
//**************************************************************************************************
//*
//*           screens handling
//*         
//*
//*
//**************************************************************************************************
//**************************************************************************************************

//****************************  includes
#include <Arduino.h>
#include <screens.h>

#define SCREEN_ADDRESS 0x22
#define SCREEN_ADDRESS 0x23
#define SCREEN_ADDRESS 0x24

//****************************  declarations
String screenAB[4] =  {
    "  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |", 
    "    |    |    |    |    |    |    |    |", 
    "    |    |    |    |    |    |    |    |",
    "    |    |    |    |    |    |    |    |" };
String screenC[4] =    {
    "Tempo: 120          ", 
    "                    ", 
    "                    ",
    "                    " };

const char customChar[8][8] = PROGMEM {{        // special characters for the initial screen
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b00000,
    0b00000,
    0b00000,
    0b00000},{

    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b11111,
    0b11111,
    0b11111,
    0b11111},{

    0b00011,
    0b01111,
    0b01111,
    0b11111,
    0b00000,
    0b00000,
    0b00000,
    0b00000},{

    0b11000,
    0b11110,
    0b11110,
    0b11111,
    0b00000,
    0b00000,
    0b00000,
    0b00000},{

    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b11111,
    0b01111,
    0b01111,
    0b00011},{

    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b11111,
    0b11110,
    0b11110,
    0b11000},{

    0b00000,
    0b00000,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b00000,
    0b00000},{

    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000}};

const char customChar2[8][8] = PROGMEM {{        // special characters for the initial screen
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b00000,
    0b00000,
    0b00000,
    0b00000},{

    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b11111,
    0b11111,
    0b11111,
    0b11111},{

    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111},{

    0b11111,
    0b11111,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000},{

    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b11111,
    0b11111},{

    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000},{

    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000},{

    0b11100,
    0b11000,
    0b11100,
    0b11000,
    0b11100,
    0b11000,
    0b11100,
    0b11000}};

LiquidCrystal_I2C screenLCDA(0x25,20,4);
LiquidCrystal_I2C screenLCDB(0x26,20,4);
LiquidCrystal_I2C screenLCDC(0x27,20,4);

//****************************  function definition

//**************************************************************************************************
//****************************  initialize screens
void screenInit(){
    screenLCDA.init();                      // initialize the lcd A
    screenLCDA.backlight();
    screenLCDB.init();                      // initialize the lcd B
    screenLCDB.backlight();
    screenLCDC.init();                      // initialize the lcd C
    screenLCDC.backlight();

    screenLCDA.home();
    screenLCDA.clear();
    screenLCDB.home();
    screenLCDB.clear();
    screenLCDC.home();
    screenLCDC.clear();
    screenLCDA.noCursor();
    screenLCDB.noCursor();
    screenLCDC.noCursor();

    for(int i=0; i<8; i++){
        screenLCDA.createChar(i, customChar[i]);
        screenLCDB.createChar(i, customChar[i]);
        screenLCDC.createChar(i, customChar[i]);
    }

}

//**************************************************************************************************
//****************************  update screen AB
void showScreenAB(){
    screenLCDA.home();
    screenLCDA.clear();
    screenLCDA.print(screenAB[0].substring(0,19));
    screenLCDA.setCursor(0,1);
    screenLCDA.print(screenAB[1].substring(0,19));
    screenLCDA.setCursor(0,2);
    screenLCDA.print(screenAB[2].substring(0,19));
    screenLCDA.setCursor(0,3);
    screenLCDA.print(screenAB[3].substring(0,19));

    screenLCDB.home();
    screenLCDB.clear();
    screenLCDB.print(screenAB[0].substring(20,39));
    screenLCDB.setCursor(0,1);
    screenLCDB.print(screenAB[1].substring(20,39));
    screenLCDB.setCursor(0,2);
    screenLCDB.print(screenAB[2].substring(20,39));
    screenLCDB.setCursor(0,3);
    screenLCDB.print(screenAB[3].substring(20,39));
}

//**************************************************************************************************
//****************************  update screen C
void showScreenC(){
    screenLCDC.home();
    screenLCDC.clear();
    screenLCDC.print(screenC[0]);
    screenLCDC.setCursor(0,1);
    screenLCDC.print(screenC[1]);
    screenLCDC.setCursor(0,2);
    screenLCDC.print(screenC[2]);
    screenLCDC.setCursor(0,3);
    screenLCDC.print(screenC[3]);
}
