/**
    Main CPP for Validate.h

    @author Ethan Bacurio
*/

#include <BikeBot.h>
#include "Validate.h"

Validate::Validate() = default;

/*
    Ternary operation that validates that the rotation speed isn't drastically
    slow or fast.

    @param rotateSpeed The rotate speed to be validated.
    @return validated rotate speed.
*/
int Validate::validatedRotateSpeed(int rotateSpeed) {
    return (rotateSpeed < MIN_ROTATION_SPEED) ? MIN_ROTATION_SPEED : rotateSpeed;
}

/*
    Ternary operation that validates that the speed is within the
    bounds of the motors accepted speed range.

    @param speed The speed to be validated.
    @return validated speed.
*/
int Validate::validatedSpeed(int speed) {
    return (speed < MIN_SPEED) ? MIN_SPEED : (speed > MAX_SPEED) ? MAX_SPEED : speed;
}