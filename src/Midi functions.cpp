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
    Serial.write(byte(0x90+channel));       // Note On channel 
    Serial.write(byte(note));               // note value
    Serial.write(byte(velocity));           // velocity
  }
  else{
    Serial1.write(byte(0x90+channel));      // Note On channel 1
    Serial1.write(byte(note));              // note value
    Serial1.write(byte(velocity));          // velocity
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
    Serial1.write(byte(0x80+channel));      // Note On channel 1
    Serial1.write(byte(note));              // note value
    Serial1.write(byte(velocity));          // velocity
  }
}

//**************************************************************************************************
//****************************  SendAftertouch
void SendAftertouche(byte port, byte channel, byte note, byte pressure) {
  if(port == 0){
    Serial.write(byte(0xA0+channel));       // Note On channel 
    Serial.write(byte(note));               // note value
    Serial.write(byte(pressure));           // velocity
  }
  else{
    Serial1.write(byte(0xA0+channel));      // Note On channel 1
    Serial1.write(byte(note));              // note value
    Serial1.write(byte(pressure));          // velocity
  }
}

//**************************************************************************************************
//****************************  SendControlChange
void SendControlChange(byte port, byte channel, byte controller, byte data) {
  if(port == 0){
    Serial.write(byte(0xB0+channel));       // Note On channel 
    Serial.write(byte(controller));         // note value
    Serial.write(byte(data));               // velocity
  }
  else{
    Serial1.write(byte(0xB0+channel));      // Note On channel 1
    Serial1.write(byte(controller));        // note value
    Serial1.write(byte(data));              // velocity
  }
}

//**************************************************************************************************
//****************************  SendProgramChange
void SendProgramChange(byte port, byte channel, byte controller, byte data) {
  if(port == 0){
    Serial.write(byte(0xB0+channel));       // Note On channel 
    Serial.write(byte(controller));         // note value
    Serial.write(byte(data));               // velocity
  }
  else{
    Serial1.write(byte(0xB0+channel));      // Note On channel 1
    Serial1.write(byte(controller));        // note value
    Serial1.write(byte(data));              // velocity
  }
}

//**************************************************************************************************
//****************************  SendPitchBend             check if it work lsb; msb
void SendPitchBend(byte port, byte channel, word data) {
  if(port == 0){
    Serial.write(byte(0xB0+channel));       // Note On channel 
    Serial.write(word(data));               // pichbend value
  }
  else{
    Serial1.write(byte(0xB0+channel));      // Note On channel 1
    Serial.write(word(data));               // pichbend value
  }
}
