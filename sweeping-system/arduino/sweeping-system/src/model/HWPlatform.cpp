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
  pButton = new ButtonImpl(BT_PIN);
  greenLed = new Led(GREEN_LED);
  redLed = new Led(RED_LED);
  pMotor = new ServoMotorImpl(MOTOR_PIN);
  pPot = new Potentiometer(POT_PIN);
}

void HWPlatform::init(){
}

Button* HWPlatform::getButton(){
  return this->pButton;
}

Potentiometer* HWPlatform::getPot(){
  return this->pPot;
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
  bool btPressed = pButton->isPressed();
  pLed->switchOn();
  pMotor->on();
  pMotor->setPosition(90);
  Logger.log("Button: " + String(btPressed ? "pressed" : " not pressed"));
  delay(1000);
  pMotor->setPosition(0);
  delay(1000);
  pMotor->off();
  pLed->switchOff();
}

