#ifndef __SONARTASK__
#define __SONARTASK__

#include "kernel/Task.h"
#include "model/Context.h"
#include "devices/Sonar.h"
#include "devices/TempSensor.h"
#include <Arduino.h>

class SonarTask: public Task {

public:
  SonarTask(Sonar* sonar, Context* pContext, TempSensor* tempSensor); 
  void tick();

private:  
  long elapsedTimeInState();
  void log(const String& msg);
  
  bool checkAndSetJustEntered();

  long stateTimestamp;
  bool justEntered;

  TempSensor* tempSensor;
  Sonar* sonar;
  Context* pContext;
  float d;
  bool active;
};

#endif