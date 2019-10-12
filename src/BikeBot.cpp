#include "BikeBot.h"
#include "Utils.h"

#define DRIVE_THRESHOLD 100
#define KP 5

int countsPerRev = 192 ;   // 4 pairs of N-S x 48:1 gearbox = 192 ticks per wheel rev

float wheelDiam = 2.56;  // diam = 65mm / 25.4 mm/in
float wheelCirc = PI * wheelDiam;

/*
 * Zero-Argument Constructor.
 *
 * Constructs bot with default speeds.
 */
BikeBot::BikeBot() {
    power = DEFAULT_POWER;
}

/**
 * Multiple-Argument Constructor.
 *
 * Constructs bot with provided parameters.
 *
 * @param _base_speed speed to initialize with.
 */
BikeBot::BikeBot(int _base_speed, int _rotate_speed) {
    power = Validate::validatedPower(_base_speed);
}

void BikeBot::rightDrive(int speed) {
    motors.rightDrive(speed);
}

void BikeBot::leftDrive(int speed) {
    motors.leftDrive(speed);
}

void BikeBot::forward(float distance) {
    driveStraight(distance);
}

void BikeBot::reverse(float distance) {
    driveStraight(distance);
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
    int offset = 2;  // offset amount to compensate Right vs. Left drive

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
    motors.brake();
}

void BikeBot::left() {
    pivot(-90);
}

void BikeBot::right() {
    pivot(90);
}

void BikeBot::stop() {
    motors.stop();
}

void BikeBot::pivot(int angle) {
    //TODO: Implement pivot function;
}

void BikeBot::pivotPrecise(float angle) {

    // use wheel encoders to pivot (turn) by specified angle

    // set motor power for pivoting
    int power = 100; // clockwise
    if (angle < 0) power *= -1; // negative power for counter-clockwise

    // use correction to improve angle accuracy
    // adjust correction value based on test results
    float correction = -17.0; // need decimal point for float value
    if (angle > 0) angle += correction;
    else if (angle < 0) angle -= correction;

    // variable for tracking wheel encoder counts
    long rightCount = 0;

    float pivotDiam = 6.125; // pivot diameter = distance between centers of wheel treads = 6.125 in
    float pivotCirc = PI * pivotDiam; // pivot circumference = 3.14 x 6.125 in = 19.23 in

    // based on angle, calculate distance (arc length) for pivot
    float distance = abs(angle) / 360.0 * pivotCirc;

    // based on distance, calculate number of wheel revolutions
    float numRev = distance / wheelCirc;

    // based on number of revolutions, calculate target encoder count
    float targetCount = numRev * countsPerRev;

    // reset encoder counters and start pivoting
    encoder.clearEnc(BOTH);
    delay(100);
    motors.pivot(power);

    // keeps looping while right encoder count less than target count
    while (abs(rightCount) < abs(targetCount)) {
        // get current wheel encoder count
        rightCount = encoder.getTicks(RIGHT);
        delay(10);  // short delay before next reading
    }

    // target count reached
    motors.brake();
}

void BikeBot::setBaseSpeed(int _baseSpeed) {
    power = _baseSpeed;
}




