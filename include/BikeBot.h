#ifndef BIKEBOT_H
#define BIKEBOT_H

#include<RedBot.h>

// Use these constants to set bounds for validations.
const int MAX_SPEED = 255;
const int MIN_SPEED = -255;

/*
    Rotation speed constants.

    Rotation speed is measured with: Degrees/Second
*/ 
const int MIN_ROTATION_SPEED = 10;
const int DEFAULT_ROTATION_SPEED = 180;
const int MAX_ROTATION_SPEED = 360;

class BikeBot {

    private: int base_speed, rotate_speed;
    
    public: 
        BikeBot(int _base_speed, int _rotate_peed);
        void forward();
        void reverse();
        void left();
        void right();
        void rotate(int angle);
        void stop();

        void setBaseSpeed(int _baseSpeed);
        void setRotateSpeed(int _rotateSpeed);
};

/**
    Class for all validation that we have to use in the future.

    Use validation when setting values for some components that could
    impact the functionality of the Bot. Stop it for potentially acting
    weird unexpectedly.

    We can also use validation to validate certain conditions that we
    could come up with in the future :).
*/
class Validate {
    public:
        Validate();
        int validatedSpeed(int speed);
        int validatedRotateSpeed(int rotateSpeed);
};

#endif