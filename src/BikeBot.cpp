#include "BikeBot.h"

RedBotMotors motors;

BikeBot::BikeBot(int _base_speed, int _rotate_speed) {
    base_speed = _base_speed;
    rotate_speed = _rotate_speed;
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
    pivot(-90);
}

void BikeBot::right() {
    pivot(90);
}

void BikeBot::stop() {
    motors.stop();
}

void BikeBot::pivot(int angle){
    int turningSpeed = 180; // degreees / second

    long turningTime;
    turningTime = (long) 1000 * angle / turningSpeed;

    motors.rightMotor(-100); // Turn CCW at motorPower of 100
    motors.leftMotor(-100);  // Turn CCW at motorPower of 100
    delay(turningTime);      // turning Time
    motors.brake();     // brake() motors
}
