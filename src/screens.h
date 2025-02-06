//**************************************************************************************************
//**************************************************************************************************
//*
//*           Header file for screens.cpp
//*         
//*
//*
//**************************************************************************************************
//**************************************************************************************************

//****************************  includes
#include <Arduino.h>
#include <string.h>
#include <Wire.h>    // I2C library
#include <LiquidCrystal_I2C.h>


//****************************  declarations
extern String screenAB[4];
extern String screenC[4];

extern const char customChar[8][8];
extern const char customChar2[8][8];

//****************************  function definition
extern void screenInit();
extern void showScreenAB();
extern void showScreenC();