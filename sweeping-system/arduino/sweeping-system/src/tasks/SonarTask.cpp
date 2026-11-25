#include "tasks/SonarTask.h"
#include "kernel/Logger.h"
#include "config.h"

SonarTask::SonarTask(Sonar* sonar, Context* pContext, TempSensorTMP36* tempSensor)
	: sonar(sonar), pContext(pContext), tempSensor(tempSensor), stateTimestamp(0), justEntered(true) {}

void SonarTask::tick() {
    bool active = pContext->isWorking() || pContext->isPreAlarm();
    if (!active || !pContext->hasNewSector()) {
        return;
    }
    pContext->clearNewSector();
    sonar->setTemperature(tempSensor->getTemperature());
    d = sonar->getDistance();
    pContext->setDistance(pContext->getSector(), d);

    valid = (d != NO_OBJ_DETECTED);
    if (valid && d < D1) {
        pContext->setAlarm();
    } else if (valid && d <= D2 && pContext->isWorking()) {
        pContext->setPreAlarm();
    } else if (pContext->isPreAlarm() && !pContext->anyObjectInRange()) {
        pContext->setWorking();
    }
}

long SonarTask::elapsedTimeInState() {
	return millis() - stateTimestamp;
}

void SonarTask::log(const String& msg) {
	Serial.println("[SonarTask] " + msg);
}

bool SonarTask::checkAndSetJustEntered() {
	if (justEntered) {
		justEntered = false;
		return true;
	}
	return false;
}
