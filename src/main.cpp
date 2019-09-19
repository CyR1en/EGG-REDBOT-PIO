
#include <BikeBot.h>

BikeBot bikeBot = BikeBot(255, 180);

void setup() {
    bikeBot.forward();
    delay(2000);
    bikeBot.stop();
}


void loop() {
    delay(200);
    Serial.println();
}

