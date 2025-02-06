//**************************************************************************************************
//**************************************************************************************************
//*
//*         keyboard handling
//*         
//*
//*
//**************************************************************************************************
//**************************************************************************************************

//****************************  includes
#include <Arduino.h>
#include <Keyboard.h>
#include <Sequencer.h>
#include <LEDs.h>

//****************************  declarations
byte keyledRows[8][2]   = {{3, 0},{3, 1},{3, 2},{3, 3},{3, 4},{3, 5},{3, 6},{3, 7}};  
byte keyCols[8][2]      = {{4, 0},{4, 1},{4, 2},{4, 3},{4, 4},{4, 5},{4, 6},{4, 7}};  // rows   columns
                    // {port, pin}  port - 0:UNO  1:PORT0A, 2:PORT0B  3:PORT1A, 4:PORT1B  pin - 0-7
byte keys[8][8][2]        ={{{0,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7}},     // rows   columns  {time, number}
                            {{0,8},{0,9},{0,10},{0,11},{0,12},{0,13},{0,14},{0,15}},
                            {{0,16},{0,17},{0,18},{0,19},{0,20},{0,21},{0,22},{0,23}},
                            {{0,24},{0,25},{0,26},{0,27},{0,28},{0,29},{0,30},{0,31}},
                            {{0,32},{0,33},{0,34},{0,35},{0,36},{0,37},{0,38},{0,39}},
                            {{0,40},{0,41},{0,42},{0,43},{0,44},{0,45},{0,46},{0,47}},
                            {{0,48},{0,49},{0,50},{0,51},{0,52},{0,53},{0,54},{0,55}},
                            {{0,56},{0,57},{0,58},{0,59},{0,60},{0,61},{0,62},{0,63}}};

byte  keysDepr[2][2]        = {{0, 0},{0, 0}};                    // rows   columns
long  keyScanTime       = 0;
int keyScanInterval     = 10;                                  // 10ms
int keyDebounceShort    = 5;                                   // 5ms
int keyDebounceLong     = 50;                                  // 50ms

//****************************  function definition
void keyboard() {
    if(millis() - keyScanTime > keyScanInterval){
        for(int i=0; i<2; i++)  {   //key rows
        setKeyRow(i, LOW);
        for(int j=0; j<2; j++)  {                           // key columns
            if(readKey(j) == LOW){              //  LOW it means key is pressed
            if(keys[i][j][0] < keyDebounceLong){keys[i][j][0] ++;}
            #ifdef DEBUGKEYBOARD            
                Serial.print("------------------------key i ");
                Serial.print(i);
                Serial.print(" j ");
                Serial.print(j);
                Serial.print(" key state ");            
                Serial.println(keys[i][j][1]);
            #endif                      
            if(keys[i][j][0] == keyDebounceShort){              //short press
                if (KEY_RUN_STOP){                           // RUN / STOP toggle
                //keys[i][j] = 5;
                seqRun = not seqRun;
                leds[LED_RUN_STOP] = seqRun;
                #ifdef CONTROLLDEBUG            
                    Serial.println(seqRun ? "RUN" : "STOP");  
                #endif            
                }
                if (KEY_TEMPO_UP){                           // tempo UP
                tempo+=1;
                seqPulse.stop();
                seqPulse.set_frequency(tempo /60.0 * 96.0);
                seqPulse.reset();
                seqPulse.start();
                #ifdef CONTROLLDEBUG            
                    Serial.print("Tempo  ");
                    Serial.println(tempo);
                #endif            
                }
                if (KEY_TEMPO_DOWN){                           // tempo DOWN
                tempo-=1;
                seqPulse.stop();
                seqPulse.set_frequency(tempo /60.0 * 96.0);
                seqPulse.reset();
                seqPulse.start();
                #ifdef CONTROLLDEBUG            
                    Serial.print("Tempo  ");
                    Serial.println(tempo);
                #endif            
                }
            }
            if(keys[i][j][0] >= keyDebounceLong){               //  long press
                if (KEY_TEMPO_UP){                           // tempo UP repetitive
                tempo+=1;
                seqPulse.stop();
                seqPulse.set_frequency(tempo /60.0 * 96.0);
                seqPulse.reset();
                seqPulse.start();
                #ifdef CONTROLLDEBUG            
                    Serial.print("Tempo  ");
                    Serial.println(tempo);
                #endif            
                }
                if (KEY_TEMPO_DOWN){                           // tempo DOWN   repetitive
                tempo-=1;
                seqPulse.stop();
                seqPulse.set_frequency(tempo /60.0 * 96.0);
                seqPulse.reset();
                seqPulse.start();
                #ifdef CONTROLLDEBUG            
                    Serial.print("Tempo  ");
                    Serial.println(tempo);
                #endif            
                }
            }
            }else{
            if(keys[i][j][0] > 0){keys[i][j][0]--;}
            #ifdef DEBUGKEYBOARD            
                Serial.print("------------------------key i ");
                Serial.print(i);
                Serial.print(" j ");
                Serial.print(j);
                Serial.print(" key state ");            
                Serial.println(keys[i][j][1]);
            #endif                      
            }
        }
        setKeyRow(i, HIGH);;
        }
        keyScanTime = millis();
    }
}

//****************************  set key row
void setKeyRow(int i, int state){
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

//****************************  read key
int readKey(int i){
    switch (keyCols[i][0]){
    case 0:
        return digitalRead(keyCols[i][1]);
        break;
    case 1:
        return MCP20.getPin(keyCols[i][1], A);
        break;
    case 2:
        return MCP20.getPin(keyCols[i][1], B);
        break;
    case 3:
        return MCP20.getPin(keyCols[i][1], A);
        break;
    case 4:
        return MCP21.getPin(keyCols[i][1], B);
        break;
    default:
        break;
    }
}