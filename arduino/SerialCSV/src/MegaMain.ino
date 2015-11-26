/*
    Ultimate main file
*/
#include "SerialCSV.ino"
#include "Movement.ino"

void setup() {
    Serial.begin(9600);
}

void loop() {
    servoX.write(10);
    
    loopSerial();

    servoX.write(90);
}
