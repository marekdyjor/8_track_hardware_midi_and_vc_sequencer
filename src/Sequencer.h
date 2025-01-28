//**************************************************************************************************
//**************************************************************************************************
//*
//*         Sequencer data structures and functions
//*         Storing and Retriving data on SD card
//*
//*
//**************************************************************************************************
//**************************************************************************************************

//****************************  includes
#include <Arduino.h>

/*
//****************************  Sequencer track descryption 
//****************************  information about track
class SeqTrackDesc {

  //****************************  attributes
  private:
  int trackID     = 0;
  byte seqLen     = 16;
  byte noteLenght = 0;
  int  noteTime   = 0;  // pulses
  byte CC1        = 0;
  byte CC2        = 0;
  String name     = "";
  bool protectedTrack ;
  bool savedToSDTrack ;
  //vector(SeqTrackPos) sequence;

  //****************************  metods
  public:
  void setTrackID(int id){trackID = id;}
  void setSeqLen(byte len){seqLen = len;}
  void setNoteLenght(byte len){noteLenght = len;}
  void setNoteTime(int time){noteTime = time;}
  void setCC1(byte cc){CC1 = cc;}
  void setCC2(byte cc){CC2 = cc;}
  void setName(String nm){name = nm;}
  void setProtectedTrack(bool prot){protectedTrack = prot;}
  void setSavedToSDTrack(bool saved){savedToSDTrack = saved;}
  int getTrackID(){return trackID;}
  byte getSeqLen(){return seqLen;}
  byte getNoteLenght(){return noteLenght;}
  int getNoteTime(){return noteTime;}
  byte getCC1(){return CC1;}
  byte getCC2(){return CC2;}
  String getName(){return name;}
  bool getProtectedTrack(){return protectedTrack;}
  bool getSavedToSDTrack(){return savedToSDTrack;}
};

//****************************  Sequencer track position
//**************************** 
class SeqTrackPos {
  
  //****************************  attributes
  private:
  int noteTime    = 0;  //  pulses
  byte note       = 0;
  byte velocity   = 0;
  byte chord      = 0;
  byte modulation = 0;
  int pitchBend   = 0;
  byte CC1Value   = 0;
  byte CC2Value   = 0;
  
  //****************************  metods
  public:
  void setNoteTime(int time){noteTime = time;}
  void setNote(byte note){note = note;}
  void setVelocity(byte vel){velocity = vel;}
  void setChord(byte ch){chord = ch;}
  void setModulation(byte mod){modulation = mod;}
  void setPitchBend(int bend){pitchBend = bend;}
  void setCC1Value(byte val){CC1Value = val;}
  void setCC2Value(byte val){CC2Value = val;}
  int getNoteTime(){return noteTime;}
  byte getNote(){return note;}
  byte getVelocity(){return velocity;}
  byte getChord(){return chord;}
  byte getModulation(){return modulation;}
  int getPitchBend(){return pitchBend;}
  byte getCC1Value(){return CC1Value;}
  byte getCC2Value(){return CC2Value;}
  void sendMIDIpacket(byte port, byte channel);
};

//****************************  Sequencer track
//****************************
class Track {
  
  //****************************  attributes
  private:
  byte Port       = 0;
  byte chanell    = 0;
  byte seqPos     = 0;
  byte scale      = 0;
  int transpoze   = 0;
  byte transMIDIPort      = 0;
  byte transMIDIChanell   = 0;
  byte transMIDIBaseNote  = 0;  
  SeqTrackDesc track;
  
  //****************************  metods
  public:
  void setPort(byte port){Port = port;}
  void setChanell(byte ch){chanell = ch;}
  void setSeqPos(byte pos){seqPos = pos;}
  void setScale(byte sc){scale = sc;}
  void setTranspoze(int tr){transpoze = tr;}
  void setTransMIDIPort(byte port){transMIDIPort = port;}
  void setTransMIDIChanell(byte ch){transMIDIChanell = ch;}
  void setTransMIDIBaseNote(byte note){transMIDIBaseNote = note;}
  void setTrack(SeqTrackDesc tr){track = tr;}
  byte getPort(){return Port;}
  byte getChanell(){return chanell;}
  byte getSeqPos(){return seqPos;}
  byte getScale(){return scale;}
  int getTranspoze(){return transpoze;}
  byte getTransMIDIPort(){return transMIDIPort;}
  byte getTransMIDIChanell(){return transMIDIChanell;}
  byte getTransMIDIBaseNote(){return transMIDIBaseNote;}
  SeqTrackDesc getTrack(){return track;}
  bool ReadTrackFromSD(int trackID);
  bool SaveTrackToSD(int trackID);  

  };

//****************************  tracks
//****************************
class Tracks {
  
  //****************************  attributes
  private:
  Track tracks[8];
  
  //****************************  metods
  public:
  void setTrack(int id, Track tr){tracks[id] = tr;}
  Track getTrack(int id){return tracks[id];}
  bool ReadTracksFromSD();
  bool SaveTracksToSD();
}*/


extern byte sequence[4][4][2];
extern int seqLen1;
extern int seqPos1;
extern int noteLen1;
extern volatile bool seqRun;
extern volatile bool note_4on, note_4off,
            note_2on, note_2off,
            note1on, note1off, 
            note2on, note2off, 
            note4on, note4off, 
            note8on, note8off,
            note16on, note16off;
extern float tempo;
extern int pulsePerSec;
extern volatile int pulseCounter;

extern volatile bool notes[9];

#define NOTE01_P 192
#define NOTE02_P  96
#define NOTE03_P  64
#define NOTE04_P  48
#define NOTE06_P  32
#define NOTE08_P  24
#define NOTE12_P  16
#define NOTE16_P  12
#define NOTE24_P   8
