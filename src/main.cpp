#include <BikeBot.h>
#include <Tasks.h>

BikeBot *bikeBot;
Tasks *tasks;

int buttonPin = 12;

void setup(){
    BikeBot bot;
    bikeBot = &bot;

    tasks = Task::construct<SRS>(&bikeBot);

    pinMode(buttonPin, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop(void){
    if (digitalRead(buttonPin) == LOW){
        bikeBot->pivotPrecise(90);
    }
}
