#ifndef __HW_PLATFORM__
#define __HW_PLATFORM__

#include "config.h"
#include "devices/Button.h"
#include "devices/Led.h"
#include "devices/ServoMotor.h"
#include "devices/Pot.h"

class HWPlatform {

public:
  HWPlatform();
  void init();
  void test();

  Button* getButton();
  Led*  getLed();
  ServoMotor* getMotor();
  Potentiometer* getPot();

private:
  Button* pButton;
  Led* pLed;
  ServoMotor* pMotor;
  Potentiometer* pPot;
  
};

#endif
