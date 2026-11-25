#include "ButtonsTask.h"
#include <Arduino.h>
#include "config.h"

ButtonsTask::ButtonsTask(Button* start, Button* stop, Button* reset, Context* pContext)
	: start(start), stop(stop), reset(reset), pContext(pContext) {
}

void ButtonsTask::tick() {
    if (pContext->isIdle() && start->isPressed()) {
        pContext->setWorking();
    } else if ((pContext->isWorking() || pContext->isPreAlarm())&& stop->isPressed()) {
        pContext->setIdle();
    } else if (pContext->isAlarm() && reset->isPressed()) {
        pContext->setWorking();
    }
}
