//
// Created by Ethan Bacurio on 9/14/19.
//

#ifndef VALIDATE_H
#define VALIDATE_H

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

    static int validatedSpeed(int speed);

    static int validatedRotateSpeed(int rotateSpeed);
};

#endif
