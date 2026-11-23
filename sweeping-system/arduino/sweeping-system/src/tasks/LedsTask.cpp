#include "tasks/LedsTask.h"
#include <Arduino.h>
#include "config.h"
#include "kernel/Logger.h"

LedsTask::LedsTask(Led* greenLed, Led* redLed, Context* pContext): 
    pContext(pContext), greenLed(greenLed), redLed(redLed){
    setState(IDLE);
}
  
void LedsTask::tick(){
    switch (state){   
    case IDLE: {
        if (this->checkAndSetJustEntered()){
            redLed->switchOff();
            greenLed->switchOff();
        }
        if (pContext->isWorking()){
            setState(WORKING);
        }
        break;
    }
    case WORKING: {
        if (this->checkAndSetJustEntered()){
            redLed->switchOff();
            greenLed->switchOn();
        }
        if (pContext->isIdle()){
            setState(IDLE);
        }
        if (pContext->isAlarm()){
            setState(ALARM);
        }
        break;
    }
    case ALARM: {
        redLed->invert();
        if (pContext->isPreAlarm() || pContext->isWorking()) {
            setState(WORKING);
        }
        break;
    }
    }
}


void LedsTask::setState(int s){
    state = s;
    stateTimestamp = millis();
    justEntered = true;
}

long LedsTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

bool LedsTask::checkAndSetJustEntered(){
    bool bak = justEntered;
    if (justEntered){
      justEntered = false;
    }
    return bak;
}
