/*
    Ultimate main file
*/
#include "SerialCSV.ino"
#include "Movement.ino"

void setup() {
    Serial.begin(9600);
}

void loop() {
    loopSerial();
    loopMovement();

    mood = 1;
}
