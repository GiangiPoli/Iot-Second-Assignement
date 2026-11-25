#ifndef __SONARTASK__
#define __SONARTASK__

#include "kernel/Task.h"
#include "model/Context.h"
#include "devices/Sonar.h"
#include "devices/TempSensorTMP36.h"
#include <Arduino.h>

class SonarTask: public Task {

public:
  SonarTask(Sonar* sonar, Context* pContext, TempSensorTMP36* tempSensor); 
  void tick();

private:  
  long elapsedTimeInState();
  void log(const String& msg);
  
  bool checkAndSetJustEntered();

  Sonar* sonar;
  Context* pContext;
  TempSensorTMP36* tempSensor;

  long stateTimestamp;
  bool justEntered;

  float d;
  bool active, valid;
};

#endif