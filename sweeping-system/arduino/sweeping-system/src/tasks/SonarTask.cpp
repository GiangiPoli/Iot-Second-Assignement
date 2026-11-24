#include "tasks/SonarTask.h"
#include "kernel/Logger.h"
#include "config.h"

SonarTask::SonarTask(Sonar* sonar, Context* pContext, TempSensor* tempSensor)
	: sonar(sonar), pContext(pContext), tempSensor(tempSensor), stateTimestamp(0), justEntered(true) {}

void SonarTask::tick() {
	if (checkAndSetJustEntered()) {
		stateTimestamp = millis();
	}
	float temperature = tempSensor->getTemperature();
    sonar->setTemperature(temperature);
    float distance = sonar->getDistance();
    if (distance != NO_OBJ_DETECTED) {
        if (distance >= D1 && distance <= D2) {
            pContext->setPreAlarm();
            Logger.log("Object detected in range");
        }
        if (distance <= D1) {
            pContext->setAlarm();
            Logger.log("Objected detecteed in danger zone pls move the radar by yourself");
        }
        
    }
	log("Sonar distance: " + String(distance) + ", Temp: " + String(temperature));
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
