#include "BikeBot.h"

int countsPerRev2 = 192;

long lCounter;
long rCounter;

/*
 * Zero-Argument Constructor.
 *
 * Constructs bot with default speeds.
 */
BikeBot::BikeBot() {
    dV = DEFAULT_ROTATION_SPEED;
    dR = DEFAULT_ROTATION_SPEED;
}

/**
 * Multiple-Argument Constructor.
 *
 * Constructs bot with provided parameters.
 *
 * @param _base_speed speed to initialize with.
 * @param _rotate_speed rotation speed to initialize with.
 */
BikeBot::BikeBot(int _base_speed, int _rotate_speed) {
    dV = Validate::validatedSpeed(_base_speed);
    dR = Validate::validatedRotateSpeed(_rotate_speed);
}

void BikeBot::forward(int revolution) {
    drive(dV, revolution);
}

void BikeBot::reverse(int revolution) {
    drive(-dV, revolution);
}

void BikeBot::drive(int _dV, int revolution) {
    if (revolution == INDEFINITE)
        motors.drive(_dV);
    else {
        encoder.clearEnc(BOTH);
        motors.drive(_dV);
        while ((lCounter < revolution * countsPerRev2) ||
               (rCounter < revolution * countsPerRev2)) {
            lCounter = encoder.getTicks(LEFT);
            rCounter = encoder.getTicks(RIGHT);
        }
        motors.brake();
    }
}

void BikeBot::left() {
    rotate(-90);
}

void BikeBot::right() {
    rotate(90);
}

void BikeBot::stop() {
    motors.stop();
}

void BikeBot::rotate(int angle) {
    long turningTime = (long) 1000 * angle / dR;

    int dV = (angle > 0) ? -100 : 100;

    motors.rightMotor(dV);
    motors.leftMotor(dV);

    delay(turningTime);
    motors.brake();
}

void BikeBot::setBaseSpeed(int _baseSpeed) {
    dV = _baseSpeed;
}

void BikeBot::setRotateSpeed(int _rotate_speed) {
    dR = _rotate_speed;
}



