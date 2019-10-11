/**
    Main CPP for Validate.h

    @author Ethan Bacurio
*/

#include <BikeBot.h>
#include "Validate.h"

Validate::Validate() = default;

/*
    Ternary operation that validates that the speed is within the
    bounds of the motors accepted speed range.

    @param speed The speed to be validated.
    @return validated speed.
*/
int Validate::validatedPower(int power) {
    return (power < MIN_POWER) ? MIN_POWER : (power > MAX_POWER) ? MAX_POWER : power;
}