#ifndef __BUTTONSTASK__
#define __BUTTONSTASK__

#include "kernel/Task.h"
#include "model/Context.h"
#include "devices/Button.h"
#include <Arduino.h>

class ButtonsTask: public Task {

public:
  ButtonsTask(Button* start, Button* stop, Button* reset, Context* pContext); 
  void tick();

private:
  Button* start;
  Button* stop; 
  Button* reset;
  Context* pContext;
};

#endif