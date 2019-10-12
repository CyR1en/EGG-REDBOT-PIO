#include "Tasks.h"

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
    //TODO
}

//executeTask() implementation for class SAW(Stop At Wall).
void SAW::executeTask(BikeBot *bikeBot) {
    //TODO
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
