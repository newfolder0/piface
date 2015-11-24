#include "ServoDrive.h"
#include <Servo.h>

// basic default constructor
ServoDrive::ServoDrive(int newPinX, int newPinY) {
    int defaultMood = 1;

    // instantiate with default angle and mood
    ServoDrive(newPinX, newPinY, defaultMood);
}

// complete constructor
ServoDrive::ServoDrive(int newPinX, int newPinY, int newMood) {
    // instantiate and set up servo
    // Servo servoX;
    // Servo servoY;

    // set initial vars
    setPins(newPinX, newPinY);
    setMood(newMood);

    // initialise default angles
    setAngles(90, 90);
    setTargets(90, 90);

    servoX.write(90);
    servoY.write(90);
}

// function to set servo pin
void ServoDrive::setPins(int newPinX, int newPinY) {
    // detach from previous, attach to new
    servoX.detach();
    servoY.detach();

    servoX.attach(newPinX);
    servoY.attach(newPinY);

    // store pin
    pinX = newPinX;
    pinY = newPinY;
}

// function to set mood
void ServoDrive::setMood(int newMood) {
    mood = newMood;
}

// function to set servo angle
void ServoDrive::setAngles(int newX, int newY) {
    angleX = newX;
    angleY = newY;
}

void ServoDrive::setTargets(int newX, int newY) {
    targetX = newX;
    targetY = newY;
}

// go to an angle
// this will only increment - asymptotic
void ServoDrive::update() {

    switch (mood) {
        case 0:
            // servoX.write(90);
            // servoY.write(90);
            break;

        case 1:
            // servoX.write(100);
            // servoY.write(100);
            break;

        default:
            break;
    }
}
