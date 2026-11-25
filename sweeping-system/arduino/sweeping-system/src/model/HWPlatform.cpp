#include "HWPlatform.h"
#include <Arduino.h>
#include "devices/ButtonImpl.h"
#include "kernel/MsgService.h"
#include "config.h"
#include "devices/Led.h"
#include "devices/LightSensorImpl.h"
#include "devices/ServoMotorImpl.h"
#include "kernel/Logger.h"
#include "devices/Pot.h"

void wakeUp(){}

HWPlatform::HWPlatform(){
  greenLed = new Led(GREEN_LED);
  redLed = new Led(RED_LED);
  pMotor = new ServoMotorImpl(MOTOR_PIN);
  pPot = new Potentiometer(POT_PIN);
  sonar = new Sonar(PROX_ECHO, PROX_TRIG, MAX_TIME);
  tempSensor = new TempSensorTMP36(TEMP_PIN);
  start = new ButtonImpl(BTN_START);
  stop = new ButtonImpl(BTN_STOP);
  reset = new ButtonImpl(BTN_RST);
}

void HWPlatform::init(){
}

Potentiometer* HWPlatform::getPot(){
  return this->pPot;
}

Sonar *HWPlatform::getSonar(){
  return sonar;
}

Button *HWPlatform::getStart(){
  return start;
}

Button *HWPlatform::getStop(){
  return stop;
}

Button *HWPlatform::getReset(){
  return reset;
}

TempSensorTMP36* HWPlatform::getTempSensor(){
  return tempSensor;
}

Led*  HWPlatform::getGreenLed(){
  return this->greenLed;
}

Led*  HWPlatform::getRedLed(){
  return this->redLed;
}

ServoMotor* HWPlatform::getMotor(){
  return this->pMotor;
}

void HWPlatform::test(){
 
}

