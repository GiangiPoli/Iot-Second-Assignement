#include "Context.h"

Context::Context(){
  preAlarm = false;
  working = false;
  alarm = false;
  idle = false;
}

bool Context::isAlarm(){
  return alarm;
}

bool Context::isIdle(){
  return idle;
}

bool Context::isPreAlarm(){
  return preAlarm;
}

bool Context::isWorking(){
  return working;
}

void Context::setIdle(){
  this->reset();
  started = true;
}

void Context::setAlarm(){
  this->reset();
  alarm = true;
}

void Context::setPreAlarm(){
  this->reset();
  preAlarm = true;
}

void Context::setWorking(){
  this->reset();
  working = true;
}

void Context::reset(){
  working = false;
  alarm = false;
  preAlarm = false;
  idel = false;
}
