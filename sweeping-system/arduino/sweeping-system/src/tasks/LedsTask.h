#ifndef __LEDSTASK__
#define __LEDSTASK__

#include "kernel/Task.h"
#include "model/Context.h"
#include "devices/Led.h"
#include <Arduino.h>

class LedsTask: public Task {

public:
  LedsTask(Led* redLed, Led* greenLed, Context* pContext); 
  void tick();

private:  
  void setState(int state);
  long elapsedTimeInState();
  void log(const String& msg);
  
  bool checkAndSetJustEntered();
  
  enum { IDLE, OFF, ON } state;
  long stateTimestamp;
  bool justEntered;

  Led* pLed;
  Context* pContext;
};

#endif