#include <BikeBot.h>
#include <Tasks.h>

BikeBot *bikeBot;
Tasks *tasks;

int buttonPin = 12;

void setup(){
    BikeBot b;
    bikeBot = &b;

    tasks = Task(*bikeBot).construct<SRS>();
    pinMode(buttonPin, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop(void){
    if (digitalRead(buttonPin) == LOW){
        tasks->executeTask();
    }
}
