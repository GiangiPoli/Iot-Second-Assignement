#include "SweepingTask.h"
#include <Arduino.h>
#include "config.h"
#include "kernel/Logger.h"

#define FWD_TIME 2000
#define BWD_TIME 1000
#define START_TIME 100
#define RESET_TIME 500


SweepingTask::SweepingTask(Button* pButton, ServoMotor* pMotor, Context* pContext): 
    pMotor(pMotor), pButton(pButton), pContext(pContext){
    setState(IDLE);
}
  
void SweepingTask::tick(){
    switch (state){    
    case IDLE: {
        
        break;
    }
    case WORKING: {        
        
        break;       
    }
    case PRE_ALARM: {        
        
        break;       
    }
    case ALARM: {
        
    }
    case RESETTING: {
        
    }
    }
}

void SweepingTask::setState(int s){
    state = s;
    stateTimestamp = millis();
    justEntered = true;
}

long SweepingTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

bool SweepingTask::checkAndSetJustEntered(){
    bool bak = justEntered;
    if (justEntered){
      justEntered = false;
    }
    return bak;
}
