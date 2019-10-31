//
// Created by Ethan Bacurio on 10/11/19.
//

#ifndef UTILS_H
#define UTILS_H

#define B_1 225.0f
#define B_2 148.0f

template<typename T>
static T sgn(T t) {
    return (T(0) < t) - (t < T(0));
}


static float calculateTicksPerRev(float power) {
    return (power >= 0 && power < 175) ?  ((-2.0f / 5.0f) * power) + B_1 :
           (power >= 175 && power <= 255) ? ((-2.0f / 25.0f ) * power) + B_2 : 0;
}

#endif
