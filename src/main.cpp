#include <BikeBot.h>
#include <Tasks.h>

BikeBot *bikeBot;
int buttonPin = 12;

void setup(){
    BikeBot bot;
    bikeBot = &bot;
    pinMode(buttonPin, INPUT_PULLUP);
    Serial.begin(9600);
}

void execute(Tasks* tasks) {
    tasks->executeTask(bikeBot);
}

void loop(void){
    if(digitalRead(buttonPin) == LOW) {
        execute(construct<SRS>(bikeBot));
/*
        bikeBot->driveStraight(18);
*/
    }
}

