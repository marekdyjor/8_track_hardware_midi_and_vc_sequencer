//**************************************************************************************************
//**************************************************************************************************
//*
//*         midi functions
//*         
//*
//*
//**************************************************************************************************
//**************************************************************************************************

//****************************  includes
#include <Arduino.h>
#include <Midi functions.h>


//**************************************************************************************************
//****************************  SendNoteOn
void SendNoteOn(byte port, byte channel, byte note, byte velocity)  {
  if(port == 0){
    Serial.write((0x90+channel));           // Note On channel 
    Serial.write(byte(note));               // note value
    Serial.write(byte(velocity));           // velocity
  }
  else{
    Serial1.write((0x90+channel));           // Note On channel 1
    Serial1.write(byte(note));               // note value
    Serial1.write(byte(velocity));           // velocity
  }
}

//**************************************************************************************************
//****************************  SendNoteOff
void SendNoteOff(byte port, byte channel, byte note, byte velocity) {
  if(port == 0){
    Serial.write(byte(0x80+channel));       // Note On channel 
    Serial.write(byte(note));               // note value
    Serial.write(byte(velocity));           // velocity
  }
  else{
    Serial1.write((0x80+channel));           // Note On channel 1
    Serial1.write(byte(note));               // note value
    Serial1.write(byte(velocity));           // velocity
  }
}

