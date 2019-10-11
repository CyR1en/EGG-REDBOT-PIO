#include <BikeBot.h>

BikeBot bikeBot;

int buttonPin = 12;

void setup(){
    pinMode(buttonPin, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop(void){
    if (digitalRead(buttonPin) == LOW){
        bikeBot.pivotPrecise(90);
    }
}
