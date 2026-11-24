#include "SweepingTask.h"
#include <Arduino.h>
#include "config.h"
#include "kernel/Logger.h"


SweepingTask::SweepingTask(Potentiometer* pPot,ServoMotor* pMotor, Context* pContext): 
    pPot(pPot), pMotor(pMotor), pContext(pContext){
    setState(IDLE);
}

void SweepingTask::resetSweep(){
    dir = 1;
    pMotor->setPosition(0);
    pContext->clearScan();
}

void SweepingTask::sweep(){
    int s = pContext->getSector() + dir;
    if (s >= N - 1) {
        s = N - 1;
        dir = -1;
    } else if (s <= 0) {
        s = 0;
        dir = 1;
    }
    pMotor->setPosition(s * 180 / (N - 1));
    pContext->setSector(s);
    pContext->setNewSector();
}
  
void SweepingTask::tick(){
    switch (state){    
    case IDLE: {
        resetSweep();
        if (pContext->isWorking()) {
            pContext->setNewSector();
            setState(WORKING);
        }
        break;
    }
    case WORKING: {
        if (pContext->isPreAlarm()) {
            setState(PRE_ALARM);
        } else if (pContext->isIdle()) {
            setState(IDLE);
        } else if (pContext->isAlarm()) {
            setState(ALARM);
        } else {
            sweep();
        }
        break;       
    }
    case PRE_ALARM: { 
        if (pContext->isAlarm()) {
            setState(ALARM);
        } else if (pContext->isWorking()) {
            setState(WORKING);
        } else {
            sweep();
        }
        break;       
    }
    case ALARM: {
        pPot->sync();
        pMotor->setPosition(pPot->getValue() * 180);
        if (pContext->isWorking()) {
            resetSweep();
            setState(WORKING);
        }
        break;
    }
    }
}

void SweepingTask::setState(int newState){
    state = newState;
    if (newState == PRE_ALARM) {
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
