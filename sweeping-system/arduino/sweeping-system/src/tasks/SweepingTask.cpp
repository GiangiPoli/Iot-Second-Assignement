#include "SweepingTask.h"
#include <Arduino.h>
#include "config.h"
#include "kernel/Logger.h"

#define N 6
#define S1 100
#define S2 50


SweepingTask::SweepingTask(Potentiometer* pPot,ServoMotor* pMotor, Context* pContext): 
    pPot(pPot), pMotor(pMotor), pContext(pContext){
    setState(IDLE);
}
  
void SweepingTask::tick(){
    switch (state){    
    case IDLE: {
        pMotor->setPosition(0);
        currentPos = 0;
        increaseAngle = 180/N;
        if (pContext->isWorking()) {
            setState(WORKING);
        }
        break;
    }
    case WORKING: {
        currentPos = currentPos + increaseAngle;
        pMotor->setPosition(currentPos);
        if (currentPos == 180 || currentPos == 0) {
            increaseAngle = -(180/N);
        }
        if (pContext->isPreAlarm()) {
            setState(PRE_ALARM);
        }
        if (pContext->isIdle()) {
            setState(IDLE);
        }
        if (pContext->isAlarm()) {
            setState(ALARM);
        }
        break;       
    }
    case PRE_ALARM: {
        currentPos = currentPos + increaseAngle;
        pMotor->setPosition(currentPos);
        if (currentPos == 180 || currentPos == 0) {
            increaseAngle = -increaseAngle;
        }    
        if (pContext->isAlarm()) {
            setState(ALARM);
        }
        if (pContext->isWorking()) {
            setState(WORKING);
        } 
        break;       
    }
    case ALARM: {
        pPot->sync();
        pMotor->setPosition(pPot->getValue() * 180);
        if (pContext->isWorking() || pContext->isPreAlarm()) {
            currentPos = 0;
            increaseAngle = 180/N;
            pMotor->setPosition(0);
            setState(pContext->isPreAlarm() ? PRE_ALARM : WORKING);
        }
        break;
    }
    }
}

void SweepingTask::setState(int s){
    state = s;
    if (s == PRE_ALARM) {
        this->setPeriod(S2);
    } else {
        this->setPeriod(S1);
    }
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
