#ifndef BIKEBOT_H
#define BIKEBOT_H

#include<RedBot.h>
#include<Validate.h>

// Use these constants to set bounds for validations.
const int MAX_POWER = 255;
const int MIN_POWER = 0;
const int DEFAULT_POWER = (MIN_POWER + MAX_POWER) / 2;


// RotaryEncoder Constants
const int INDEFINITE = -1;

class BikeBot {

public:
    int power;
    RedBotMotors motors;
    RedBotEncoder encoder = RedBotEncoder(A2, 10);
    RedBotSensor leftSensor = RedBotSensor(A3);   // initialize a left sensor object on A3
    RedBotSensor centerSensor = RedBotSensor(A6); // initialize a center sensor object on A6
    RedBotSensor rightSensor = RedBotSensor(A7);  // initialize a right sensor object on A7
    Validate validator;

public:
    BikeBot();

    BikeBot(int _base_speed, int _rotate_peed);

    void forward(float distance = INDEFINITE);

    void reverse(float distance = INDEFINITE);

    void left();

    void right();

    void pivot(int angle);

    void stop();

    void setBaseSpeed(int _baseSpeed);

    void rightDrive(int pwr);

    void leftDrive(int speed);

    void driveStraight(float distance, int motorPower = DEFAULT_POWER);

    void lineFollow();

    void pivotPrecise(float angle);
};


#endif