#ifndef __CONTEXT__
#define __CONTEXT__

class Context {

public:
  Context();

  void setWorking();
  void setPreAlarm();
  void setAlarm();
  void setIdle();

  bool isAlarm();  
  bool isPreAlarm();
  bool isWorking();
  bool isIdle();
  void reset();

private:

  bool preAlarm; 
  bool alarm;
  bool working;
  bool idle;
};

#endif
