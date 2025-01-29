//**************************************************************************************************
//**************************************************************************************************
//*
//*         interrupts, timer handling
//*         
//*
//*
//**************************************************************************************************
//**************************************************************************************************

//****************************  includes
#include <Arduino.h>
#include <Interrupts.h>

//****************************  create timer object
 FspTimer seqPulse;

//**************************************************************************************************
//****************************  interrupt timer callbackMain
void timer_callback(timer_callback_args_t __attribute((unused)) *p_args){
    if(pulseCounter==0){
      note1on   = true;
      note2on   = true;
      note4on   = true;
      note8on   = true;
      note16on  = true;
    }
    
          
    if(pulseCounter % NOTE01_P == 0){
      note1on = true;
    }
    if(note1on and pulseCounter % (NOTE01_P/8) == 0){
      noteLen--;
      if(noteLen >=0){
        note1off = true;
        note1on = false;
      } 
    }
    
    /*if(pulseCounter % 24 == 0 and pulseCounter % 48 == 0 ){
      note2on = true;
    }
    if(pulseCounter % 24 == 0 and pulseCounter % 48 != 0 ){
      note2off = true;
    }

    if(pulseCounter % 12 == 0 and pulseCounter % 24 == 0 ){
      note4on = true;
    }
    if(pulseCounter % 12 == 0 and pulseCounter % 24 != 0 ){
      note4off = true;
    }*/

    pulseCounter++;
}

//**************************************************************************************************
//****************************  initialize Timer
bool beginTimer(float rate) {
  uint8_t timer_type = GPT_TIMER;
  int8_t tindex;
  tindex = FspTimer::get_available_timer(timer_type);
  if (tindex < 0){
    tindex = FspTimer::get_available_timer(timer_type, true);
  }
  if (tindex < 0){
    return false;
  }

  FspTimer::force_use_of_pwm_reserved_timer();

  if(!seqPulse.begin(TIMER_MODE_PERIODIC, timer_type, tindex, rate, 0.0f, timer_callback)){
    return false;
  }

  if (!seqPulse.setup_overflow_irq()){
    return false;
  }

  if (!seqPulse.open()){
    return false;
  }

  if (!seqPulse.start()){
    return false;
  }
  return true;
}