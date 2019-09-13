#include "BikeBot.h"

RedBotMotors motors;
Validate validator;

BikeBot::BikeBot(int _base_speed, int _rotate_speed) {
    base_speed = validator.validatedSpeed(_base_speed);
    rotate_speed = validator.validatedRotateSpeed(_rotate_speed);
}

void BikeBot::forward() {
    motors.drive(base_speed);
}

void BikeBot::reverse() {
    motors.drive(-255);
    delay(500);
    motors.brake();
    delay(100); 
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

void BikeBot::rotate(int angle){
    long turningTime = (long) 1000 * angle / rotate_speed;
    
    int dV = (angle > 0) ? -100 : 100;

    motors.rightMotor(dV); 
    motors.leftMotor(dV);

    delay(turningTime); 
    motors.brake();
}

void BikeBot::setBaseSpeed(int _baseSpeed) {
    base_speed = _baseSpeed;
}

void BikeBot::setRotateSpeed(int _rotate_speed) {
    rotate_speed = _rotate_speed;
}

