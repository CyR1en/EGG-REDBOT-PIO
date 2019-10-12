#ifndef TASKS_H
#define TASKS_H

#include "BikeBot.h"

/**
 * Abstraction class for tasks.
 *
 * This class contains an abstract function 'executeTask' that would be
 * called later on.
 */
class Tasks {
public:
    BikeBot *bikeBot;

    explicit Tasks(BikeBot *_bikeBot);

    virtual void executeTask() = 0;
};

/**
 * Derived class from Tasks.
 *
 * This is the class for the task: Straight Right Straight.
 *
 * Goal: Straight 18 in, Right 90 deg, Straight 13 in.
 *
 * Tolerance: |3| inches for each leg, |5| degrees for the turn.
 */
class SRS : public Tasks {
public:
    explicit SRS(BikeBot *_bikeBot);

    void executeTask() final;
};

/**
 * Derived class from Tasks.
 *
 * This is the class for the task: Line Follow.
 *
 * Goal: Robot must be able to follow this to
 * the end with only the left and right line-follower sensors.
 *
 * Tolerance: Robot must not leave the path, and robot must reach the end of the path
 */
class LF : public Tasks {
public:
    explicit LF(BikeBot *_bikeBot);

    void executeTask() final;
};

/**
 * Derived class from Tasks.
 *
 * This is the class for the task: Stop at Wall.
 *
 * Goal: Robot must be able to drive until it reaches within 6 inches of the wall, and then stop.
 *
 * Tolerances: Front of robot remains stationary between 5-7 inches from the wall.
 */
class SAW : public Tasks {
public:
    explicit SAW(BikeBot *_bikeBot);

    void executeTask() final;
};

/**
 * This class allows us to access different tasks easily by
 * making this class construct the derived tasks
 */
class Task {
public:

    /**
     * First approach logic:
     * Be able to choose from these task and pass it down to
     * construct(Choice c) and let it construct using switch statements.
     *
     * But discovered templates :>
     */
    enum Choice {
        srs, lf, saw
    };

    //BikeBot instance, since it's needed for us to be able to construct tasks.
    BikeBot bikeBot;

    //constructor for task, so we can pass down an instance of BikeBot in this class.
    explicit Task(BikeBot _bikeBot);

    /**
     * Use a switch statement and depending on the case, construct the respective
     * task that's being requested.
     *
     * Usage: Task(bikeBotInstance).construct(Task::Choice::srs);
     *
     * @param c Choice of task.
     * @return Return address of the constructed task.
     */
    [[deprecated("Replaced by construct(), which uses template to construct generic tasks. "
    "\n Usage: construct<TasksClass>()")]]
    Tasks *construct(Choice c);

    /**
     * Use template to generically provide a task and construct it.
     *
     * Usage: Task(bikeBotInstance).construct<SRS>();
     * Compilation error will occur when T isn't a Derived class of Task.
     *
     * @tparam T Derived class of Tasks.
     * @return Return address of the constructed task.
     */
    template<class T>
    static Tasks *construct(BikeBot **bikeBot) {
        T temp(*bikeBot); //locale var; will be allocated a space in the stack.
        T *t = &temp;    //Move to heap. don't delete because it's used in the loop() func.
        return t;        //Return address.
    }
};

#endif
