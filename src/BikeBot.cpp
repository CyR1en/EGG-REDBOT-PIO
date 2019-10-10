#include "BikeBot.h"

int countsPerRev = 192;   // 4 pairs of N-S x 48:1 gearbox = 192 ticks per wheel rev

float wheelDiam = 2.56;  // diam = 65mm / 25.4 mm/in
float wheelCirc = PI*wheelDiam;

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

void BikeBot::rightDrive(int speed) {
    motors.rightDrive(speed);
}

void BikeBot::leftDrive(int speed) {
    motors.leftDrive(speed);
}

void BikeBot::forward(int revolution) {
    drive(dV, revolution);
}

void BikeBot::reverse(int revolution) {
    drive(-dV, revolution);
}

void BikeBot::driveStraight(float distance, int motorPower) {
    long lCount = 0;
    long rCount = 0;
    long targetCount;
    float numRev;

    // variables for tracking the left and right encoder counts
    long prevlCount, prevrCount;

    long lDiff, rDiff;  // diff between current encoder count and previous count

    // variables for setting left and right motor power
    int leftPower = motorPower;
    int rightPower = motorPower;

    // variable used to offset motor power on right vs left to keep straight.
    int offset = 5;  // offset amount to compensate Right vs. Left drive

    numRev = distance / wheelCirc;  // calculate the target # of rotations
    targetCount = numRev * countsPerRev;    // calculate the target count

    // debug
    Serial.print("driveStraight() ");
    Serial.print(distance);
    Serial.print(" inches at ");
    Serial.print(motorPower);
    Serial.println(" power.");

    Serial.print("Target: ");
    Serial.print(numRev, 3);
    Serial.println(" revolutions.");
    Serial.println();

    // print out header
    Serial.print("Left\t");   // "Left" and tab
    Serial.print("Right\t");  // "Right" and tab
    Serial.println("Target count");
    Serial.println("============================");

    encoder.clearEnc(BOTH);    // clear the encoder count
    delay(100);  // short delay before starting the motors.

    motors.drive(motorPower);  // start motors

    while (rCount < targetCount)
    {
        // while the right encoder is less than the target count -- debug print
        // the encoder values and wait -- this is a holding loop.
        lCount = encoder.getTicks(LEFT);
        rCount = encoder.getTicks(RIGHT);
        Serial.print(lCount);
        Serial.print("\t");
        Serial.print(rCount);
        Serial.print("\t");
        Serial.println(targetCount);

        motors.leftDrive(leftPower);
        motors.rightDrive(rightPower);

        // calculate the rotation "speed" as a difference in the count from previous cycle.
        lDiff = (lCount - prevlCount);
        rDiff = (rCount - prevrCount);

        // store the current count as the "previous" count for the next cycle.
        prevlCount = lCount;
        prevrCount = rCount;

        // if left is faster than the right, slow down the left / speed up right
        if (lDiff > rDiff)
        {
            leftPower = leftPower - offset;
            rightPower = rightPower + offset;
        }
            // if right is faster than the left, speed up the left / slow down right
        else if (lDiff < rDiff)
        {
            leftPower = leftPower + offset;
            rightPower = rightPower - offset;
        }
        delay(50);  // short delay to give motors a chance to respond.
    }
    // now apply "brakes" to stop the motors.
    motors.brake();
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

    Serial.print("Angle: \t"); Serial.println(angle);
    Serial.print("DV: \t"); Serial.println(dV);
    long turningTime = angle * ((2.514 * PI)/abs(dV));
    Serial.print("Turning Time:\t");
    Serial.println(turningTime);

    int _dV = (angle > 0) ? -dV : dV;

    motors.rightMotor(_dV);
    motors.leftMotor(_dV);

    delay(turningTime);

    motors.brake();
}

void BikeBot::pivotAngle(float angle) {

}

void BikeBot::setBaseSpeed(int _baseSpeed) {
    dV = _baseSpeed;
}

void BikeBot::setRotateSpeed(int _rotate_speed) {
    dR = _rotate_speed;
}



