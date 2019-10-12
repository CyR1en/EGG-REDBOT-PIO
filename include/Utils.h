//
// Created by Ethan Bacurio on 10/11/19.
//

#ifndef UTILS_H
#define UTILS_H


template <typename T> static T sgn(T t) {
    return (T(0) < t) - (t < T(0));
}

#endif
