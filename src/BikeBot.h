#ifndef BIKEBOT_H
#define BIKEBOT_H

#include<RedBot.h>

const int MAX_SPEED = 255;
const int DEF_ROTATE_SPEED = 180;

class BikeBot {

    private: int base_speed, rotate_speed;
    
    public: 
        BikeBot(int _base_speed, int _rotate_peed);
        void forward();
        void reverse();
        void left();
        void right();
        void pivot(int angle);
        void stop();
};

#endif