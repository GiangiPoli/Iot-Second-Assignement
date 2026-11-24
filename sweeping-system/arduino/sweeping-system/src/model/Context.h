#ifndef __CONTEXT__
#define __CONTEXT__

#include "config.h"

class Context {

public:
  Context();

  void setWorking();
  void setPreAlarm();
  void setAlarm();
  void setIdle();
  void clearNewSector();
  void setNewSector();
  void setSector(int i);
  int getSector();
  void clearScan();

  bool isAlarm();  
  bool isPreAlarm();
  bool isWorking();
  bool isIdle();
  bool hasNewSector();
  bool anyObjectInRange();

  void setDistance(int i, float d);
  float getDistance(int i);

private:

  float distances[N];
  bool newSector;
  int sector;
  enum SystemState { ST_IDLE, ST_WORKING, ST_PRE_ALARM, ST_ALARM };
  SystemState state;
};

#endif
