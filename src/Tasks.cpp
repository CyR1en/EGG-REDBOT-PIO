#include <Utils.h>
#include "Tasks.h"


#define LINE_THRESHOLD 800
#define SPEED 60
/**
 * Instead of manually setting a task, let this function construct the task and set it to the pointer.
 * Switch statement for the enum Task::Choice. The logic for each case is as follows:
 * 1. Declare a locale scope of the task 'c_var', and it will be allocated a space in the stack.
 * 2. Declare a pointer for the task '*var', and move the c_var to the heap by getting the address of 'c_var'.
 * 3. Return the pointer '*var' as 'var'.
 */
Tasks *Task::construct(Choice c) {
    switch (c) {
        case srs: {
            SRS c_srs;
            SRS *srs = &c_srs;
            return srs;
        }
        case lf: {
            LF c_lf;
            LF *lf = &c_lf;
            return lf;
        }
        case saw: {
            SAW c_saw;
            SAW *saw = &c_saw;
            return saw;
        }
    }
    return nullptr;
}

//executeTask() implementation for class SRS(Straight Right Straight).
void SRS::executeTask(BikeBot *bikeBot) {
    bikeBot->driveStraight(18); //drive 18 in
    bikeBot->pivotPrecise(90);    //pivot 90 deg
    bikeBot->driveStraight(36); //drive 36 in
}

//executeTask() implementation for class LF(Line Follow).
void LF::executeTask(BikeBot *bikeBot) {

    int leftSpeed;   // variable used to store the leftMotor speed
    int rightSpeed;  // variable used to store the rightMotor speed

    bool stopped = false;

    while(!stopped) {
        Serial.print(bikeBot->leftSensor.read());
        Serial.print("\t");  // tab character
        Serial.print(bikeBot->centerSensor.read());
        Serial.print("\t");  // tab character
        Serial.print(bikeBot->rightSensor.read());
        Serial.println();

        if (bikeBot->rightSensor.read() > LINE_THRESHOLD) {
            leftSpeed = -(SPEED + 50);
            rightSpeed = SPEED - 50;
        } else if (bikeBot->leftSensor.read() > LINE_THRESHOLD) {
            leftSpeed = -(SPEED - 50);
            rightSpeed = SPEED + 50;
        }

        bikeBot->motors.leftMotor(leftSpeed);
        bikeBot->motors.rightMotor(rightSpeed);

        delay(50);
    }
}

//executeTask() implementation for class SAW(Stop At Wall).
void SAW::executeTask(BikeBot *bikeBot) {
    float distance = 100;
    int motorPower = 150;
    bool running = true;

    float wheelDiam = 2.56;  // diam = 65mm / 25.4 mm/in
    float wheelCirc = PI * wheelDiam;

    long lCount = 0;
    long rCount = 0;
    float targetCount;
    float numRev;

    // variables for tracking the left and right encoder counts
    long prevlCount, prevrCount;

    long lDiff, rDiff;  // diff between current encoder count and previous count

    // variables for setting left and right motor power
    int leftPower = sgn(distance) * motorPower;
    int rightPower = sgn(distance) * motorPower;

    // variable used to offset motor power on right vs left to keep straight.
    int offset = sgn(distance) * 5;  // offset amount to compensate Right vs. Left drive

    numRev = distance / wheelCirc;  // calculate the target # of rotations
    targetCount = numRev * calculateTicksPerRev((float) motorPower);    // calculate the target count

    // debug
    Serial.print("driveStraight() ");
    Serial.print(distance);
    Serial.print(" inches at ");
    Serial.print(motorPower);
    Serial.println(" power.");

    Serial.print("Target: ");
    Serial.print(numRev, 3);
    Serial.print(" revolutions. ");
    Serial.print("With Ticks/Rev of ");
    Serial.println(calculateTicksPerRev((float) motorPower));
    Serial.println();

    // print out header
    Serial.print("Left\t");   // "Left" and tab
    Serial.print("Right\t");  // "Right" and tab
    Serial.println("Target count");
    Serial.println("============================");

    bikeBot->encoder.clearEnc(BOTH);    // clear the encoder count
    delay(100);  // short delay before starting the motors.

    bikeBot->motors.drive(motorPower);  // start motors

    while (((targetCount - rCount) > 2) && running) {
        // while the right encoder is less than the target count -- debug print
        // the encoder values and wait -- this is a holding loop.
        lCount = bikeBot->encoder.getTicks(LEFT);
        rCount = bikeBot->encoder.getTicks(RIGHT);
        Serial.print(lCount);
        Serial.print("\t");
        Serial.print(rCount);
        Serial.print("\t");
        Serial.println(targetCount);

        bikeBot->motors.leftDrive(leftPower);
        bikeBot->motors.rightDrive(rightPower);

        // calculate the rotation "speed" as a difference in the count from previous cycle.
        lDiff = (lCount - prevlCount);
        rDiff = (rCount - prevrCount);

        // store the current count as the "previous" count for the next cycle.
        prevlCount = lCount;
        prevrCount = rCount;

        // if left is faster than the right, slow down the left / speed up right
        if (lDiff > rDiff) {
            leftPower = leftPower - offset;
            rightPower = rightPower + offset;
        }
            // if right is faster than the left, speed up the left / slow down right
        else if (lDiff < rDiff) {
            leftPower = leftPower + offset;
            rightPower = rightPower - offset;
        }

        if(bikeBot->centerSensor.read() > 250) {
            bikeBot->motors.brake();
            running = false;
        }
        delay(10);  // short delay to give motors a chance to respond.
    }
    // now apply "brakes" to stop the motors.
    bikeBot->motors.brake();
}

void Dance::executeTask(BikeBot *bikeBot) {
    bikeBot->pivotPrecise(30);
    delay(100);
    bikeBot->pivotPrecise(-30);
    delay(100);
    bikeBot->pivotPrecise(-30);
    delay(100);
    bikeBot->pivotPrecise(30);
    delay(100);
    bikeBot->pivotPrecise(360);
    delay(100);
    bikeBot->pivotPrecise(-330);
}

void ShakeHead::executeTask(BikeBot *bikeBot) {
    bikeBot->pivotPrecise(30);
    delay(100);
    bikeBot->pivotPrecise(-60);
    delay(100);
    bikeBot->pivotPrecise(60);
    delay(100);
    bikeBot->pivotPrecise(-30);
    delay(100);
}
