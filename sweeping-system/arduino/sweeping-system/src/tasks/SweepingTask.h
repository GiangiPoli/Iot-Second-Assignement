#ifndef __SWEEPING_TASK__
#define __SWEEPING_TASK__

#include "kernel/Task.h"
#include "devices/ServoMotor.h"
#include "devices/Button.h"
#include "devices/Pot.h"
#include "model/Context.h"
#include <Arduino.h>

class SweepingTask: public Task {

public:
  SweepingTask(Potentiometer* pPot,ServoMotor* pMotor, Context* pContext); 
  void tick();

private:  
  void setState(int state);
  long elapsedTimeInState();
  void log(const String& msg);
  void resetSweep();
  void sweep();
  bool checkAndSetJustEntered();
  
  enum { IDLE, WORKING, PRE_ALARM, ALARM} state;
  long stateTimestamp;
  bool justEntered;

  ServoMotor* pMotor;
  Context* pContext;
  Potentiometer* pPot;

  int dir;
  int increaseAngle;
  bool toBeStopped;
};

#endif