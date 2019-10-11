#include "Tasks.h"

Tasks::Tasks(BikeBot _bikeBot) {
    bikeBot = _bikeBot;
}

//Implement constructors for all class derived from tasks class.
SRS::SRS(BikeBot _bikeBot) : Tasks(_bikeBot) {}
LF::LF(BikeBot _bikeBot) : Tasks(_bikeBot) {}
SAW::SAW(BikeBot _bikeBot) : Tasks(_bikeBot) {}

//executeTask() implementation for class SRS(Straight Right Straight).
void SRS::executeTask() {
    bikeBot.driveStraight(15); //drive 18 in
    bikeBot.pivotPrecise(90);    //pivot 90 deg
    bikeBot.driveStraight(10); //drive 13 in
}

//executeTask() implementation for class LF(Line Follow).
void LF::executeTask() {
    //TODO
}

//executeTask() implementation for class SAW(Stop At Wall).
void SAW::executeTask(){
    //TODO
}

//Constructor implementation for class Task
Task::Task(BikeBot _bikeBot) {
    bikeBot = _bikeBot;
}

/**
 * Instead of manually setting a task, let this function construct the task and set it to the pointer.
 * Switch statement for the enum Task::Choice. The logic for each case is as follows:
 * 1. Declare a locale scope of the task 'c_var', and it will be allocated a space in the stack.
 * 2. Declare a pointer for the task '*var', and move the c_var to the heap by getting the address of 'c_var'.
 * 3. Return the pointer '*var' as 'var'.
 */
Tasks * Task::construct(Choice c) {
    switch(c) {
        case srs: {
            SRS c_srs(bikeBot);
            SRS *srs = &c_srs;
            return srs;
        }
        case lf: {
            LF c_lf(bikeBot);
            LF *lf = &c_lf;
            return lf;
        }
        case saw: {
            SAW c_saw(bikeBot);
            SAW *saw = &c_saw;
            return saw;
        }
    }
    return nullptr;
}