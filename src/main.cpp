/***********************************************************************
 * Exp7_3_DriveStraight -- RedBot Experiment 7.3
 *
 * Knowing where your robot is can be very important. The RedBot supports
 * the use of an encoder to track the number of revolutions each wheels has
 * made, so you can tell not only how far each wheel has traveled but how
 * fast the wheels are turning.
 *
 * This sketch was written by SparkFun Electronics, with lots of help from
 * the Arduino community. This code is completely free for any use.
 *
 * 8 Oct 2013 M. Hord
 * Revised, 31 Oct 2014 B. Huang
 ***********************************************************************/
#include <RedBot.h>
#include <BikeBot.h>

BikeBot bikeBot;

int buttonPin = 12;

void setup(){
    pinMode(buttonPin, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop(void){
    if (digitalRead(buttonPin) == LOW){
        bikeBot.setRotateSpeed(100);
        bikeBot.rotate(90);
    }
}
