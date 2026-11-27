#include <Arduino.h>
#include "config.h"
#include "kernel/Scheduler.h"
#include "kernel/Logger.h"
#include "kernel/MsgService.h"
#include "model/HWPlatform.h"
#include "tasks/TestHWTask.h"
#include "tasks/SweepingTask.h"
#include "tasks/LedsTask.h"
#include "tasks/ButtonsTask.h"
#include "tasks/SonarTask.h"

//#define __TESTING_HW__

Scheduler sched;

HWPlatform* pHWPlatform;
Context* pContext;

void setup() {
  MsgService.init();
  sched.init(SCHED_PERIOD);

  Logger.log(":::::: Sweeping System ::::::");
  
  pHWPlatform = new HWPlatform();
  pHWPlatform->init();

#ifndef __TESTING_HW__
  pContext = new Context();

  Task* pSweepingTask = new SweepingTask(pHWPlatform->getPot(), pHWPlatform->getMotor(), pContext);
  pSweepingTask->init(MOTOR_PERIOD);

  Task* pLedsTask = new LedsTask(pHWPlatform->getGreenLed(), pHWPlatform->getRedLed(), pContext);
  pLedsTask->init(LEDS_PERIOD);

  Task* pSonarTask = new SonarTask(pHWPlatform->getSonar(), pContext, pHWPlatform->getTempSensor());
  pSonarTask->init(SONAR_PERIOD);

  Task* pButtonsTask = new ButtonsTask(pHWPlatform->getStart(), pHWPlatform->getStop(), pHWPlatform->getReset(), pContext);
  pButtonsTask->init(BUTTONS_PERIOD);

  sched.addTask(pSweepingTask);
  sched.addTask(pLedsTask);
  sched.addTask(pButtonsTask);
  sched.addTask(pSonarTask);
#endif

#ifdef __TESTING_HW__
  /* Testing */
  Task* pTestHWTask = new TestHWTask(pHWPlatform);
  pTestHWTask->init(2000);
  sched.addTask(pTestHWTask);
#endif
}

void loop() {
    sched.schedule();
}