//
// Created by Ethan Bacurio on 11/18/19.
//

#include "Tasks.h"

#define SPEED 120

//executeTask() implementation for class LF(Line Follow).
void LF::executeTask(BikeBot *bikeBot) {
    Serial.println("Executed LF");
    running = true;
    Serial.print("Running: "); Serial.println(running);
    while (running) {
        update(bikeBot);
        delay(50);
    }
}

void LF::update(BikeBot *bikeBot) {
    if (!deviated) {
        updateMainLineFollow(bikeBot);
        updateDeviationCheck(bikeBot);
        updateStopper(bikeBot);
    } else {
        correctBot(bikeBot);
    }
}

void LF::updateMainLineFollow(BikeBot *bikeBot) {
    int sensorContrast = getContrast(bikeBot);
    if (abs(sensorContrast) < lineContrast) {
        Serial.print("[S] ");
        bikeBot->motors.drive(SPEED);
    } else if (sensorContrast > lineContrast) {
        Serial.print("[L] ");
        bikeBot->motors.leftStop();
        bikeBot->motors.rightDrive(SPEED);
        recordLastHit(LEFT_SENSOR);
    } else {
        Serial.print("[R] ");
        bikeBot->motors.rightStop();
        bikeBot->motors.leftDrive(SPEED);
        recordLastHit(RIGHT_SENSOR);
    }
    Serial.println(sensorContrast);
}

void LF::updateContrast(BikeBot *bikeBot) {
    if (getContrast(bikeBot) > lineContrast) {
        recordLastHit(LEFT_SENSOR);
    } else if (getContrast(bikeBot) < -lineContrast) {
        recordLastHit(RIGHT_SENSOR);
    }
}

void LF::recordLastHit(byte sensor) {
    lastHitMillis = millis();
    lastHit = sensor;
}

void LF::updateDeviationCheck(BikeBot *bikeBot) {
    if ((millis() - lastHitMillis) > 2000)
        deviated = true;
}

void LF::updateStopper(BikeBot *bikeBot) {
    if (bikeBot->centerSensor.read() > 250) {
        bikeBot->motors.brake();
        running = false;
    }
}

int LF::getContrast(BikeBot *bikeBot) {
    return bikeBot->leftSensor.read() - bikeBot->rightSensor.read();
}

void LF::correctBot(BikeBot *bikeBot) {
    int vector = lastHit == RIGHT_SENSOR ? 70 : -70;
    int target = lastHit == RIGHT_SENSOR ? LEFT_SENSOR : RIGHT_SENSOR;

    while (lastHit != target) {
        bikeBot->motors.pivot(vector);
        updateContrast(bikeBot);
    }

    bikeBot->pivotPrecise(target == RIGHT_SENSOR ? 5 : -5);
    deviated = false;
}
