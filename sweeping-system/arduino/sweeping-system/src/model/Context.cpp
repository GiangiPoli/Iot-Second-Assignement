#include "Context.h"

Context::Context(){
  state = ST_IDLE;
  clearScan();
}

bool Context::isAlarm(){
  return this->state == ST_ALARM;
}

bool Context::isIdle(){
  return this->state == ST_IDLE;
}

bool Context::hasNewSector(){
  return this->newSector;
}

bool Context::anyObjectInRange(){
  for (int i = 0; i < N; i++) {
    if (distances[i] != NO_OBJ_DETECTED && distances[i] <= D2) return true;
  }
  return false;
}

void Context::setDistance(int i, float d){
  if (i >= 0 && i < N) {
    this->distances[i] = d;
  }
}

float Context::getDistance(int i){
  if (i >= 0 && i < N) {
    return this->distances[i];
  }
  return NO_OBJ_DETECTED;
}

bool Context::isPreAlarm(){
  return this->state == ST_PRE_ALARM;
}

bool Context::isWorking(){
  return this->state == ST_WORKING;
}

void Context::setIdle(){
  state = ST_IDLE;
  clearScan();
}

void Context::clearNewSector(){
  this->newSector = false;
}

void Context::setNewSector(){
  this->newSector = true;
}

void Context::setSector(int i){
  this->sector = i;
}

int Context::getSector(){
  return this->sector;
}

void Context::clearScan(){
  this->sector = 0;
  for (int i = 0; i < N; i++) {
    distances[i] = NO_OBJ_DETECTED;
  }
  this->newSector = false;
}

void Context::setAlarm(){
  state = ST_ALARM;
}

void Context::setPreAlarm(){
  state = ST_PRE_ALARM;
}

void Context::setWorking(){
  state = ST_WORKING;
}


