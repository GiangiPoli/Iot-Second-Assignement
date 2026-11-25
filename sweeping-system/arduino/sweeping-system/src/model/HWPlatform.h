#ifndef __HW_PLATFORM__
#define __HW_PLATFORM__

#include "config.h"
#include "devices/Button.h"
#include "devices/Led.h"
#include "devices/ServoMotor.h"
#include "devices/Pot.h"
#include "devices/ButtonImpl.h"
#include "devices/TempSensorTMP36.h"
#include "devices/Sonar.h"

class HWPlatform {

public:
  HWPlatform();
  void init();
  void test();

  Led*  getGreenLed();
  Led*  getRedLed();
  ServoMotor* getMotor();
  Potentiometer* getPot();
  Sonar* getSonar();
  Button* getStart();
  Button* getStop();
  Button* getReset();
  TempSensorTMP36* getTempSensor();


private:
  Led* greenLed;
  Led* redLed;
  ServoMotor* pMotor;
  Potentiometer* pPot;
  Sonar* sonar;
  ButtonImpl* start;
  ButtonImpl* stop;
  ButtonImpl* reset;
  TempSensorTMP36* tempSensor;
  
};

#endif
