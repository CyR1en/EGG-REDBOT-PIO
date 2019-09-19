#ifndef BIKEBOT_H
#define BIKEBOT_H

#include<RedBot.h>
#include<Validate.h>

// Use these constants to set bounds for validations.
const int MAX_SPEED = 255;
const int MIN_SPEED = 0;
const int DEFAULT_SPEED = (MIN_SPEED + MAX_SPEED) / 2;

/*
 *  Rotation speed constants.
 *  Rotation speed is measured with: Degrees/Second
 */
const int MIN_ROTATION_SPEED = 10;
const int MAX_ROTATION_SPEED = 360;
const int DEFAULT_ROTATION_SPEED = (MIN_ROTATION_SPEED + MAX_ROTATION_SPEED) / 2;

// RotaryEncoder Constants
const int INDEFINITE = -1;

class BikeBot {

private:
    int dV, dR;
    RedBotMotors motors;
    RedBotEncoder encoder = RedBotEncoder(A2, 10);
    Validate validator;

public:
    BikeBot();

    BikeBot(int _base_speed, int _rotate_peed);

    void forward(int revolution = INDEFINITE);

    void reverse(int revolution = INDEFINITE);

    void left();

    void right();

    void rotate(int angle);

    void stop();

    void setBaseSpeed(int _baseSpeed);

    void setRotateSpeed(int _rotateSpeed);

    void drive(int dV, int revolution);
};


#endif