/*
    Ultimate main file
*/
#include "SerialCSV.ino"
#include "Movement.ino"

void setup() {
    Serial.begin(9600);
}

void loop() {
    // active if face detected, dormant otherwise
    if (numFaces > 0) mood = 1;
    else mood = -1;

    int oldFaceSize = faceSize;

    loopSerial();
    if (abs(faceSize - oldFaceSize) > 10) loopMovement();
}
