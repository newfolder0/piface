#include "ServoDrive.h"
#include <Servo.h>

// basic default constructor
ServoDrive::ServoDrive(int newPin) {
    int defaultAngle = 90;
    int defaultMood = 1;

    // instantiate with default angle and mood
    ServoDrive(newPin, defaultAngle, defaultMood);
}

// complete constructor
ServoDrive::ServoDrive(int newPin, int newAngle, int mood) {
    // instantiate and set up servo
    Servo servo;

    // set initial vars
    setPin(newPin);
    setAngle(newAngle);
    setMood(newMood);
}

// function to set servo angle
void ServoDrive::setAngle(int newAngle) {
    servo.write(newAngle);
    angle = newAngle;
}

// function to set servo pin
void ServoDrive::setPin(int newPin) {
    // detach from previous, attach to new
    servo.detach();
    servo.attach(newPin);

    // store pin
    servoPin = newPin;
}

// function to set mood
void ServoDrive::setMood(int newMood) {
    mood = newMood;
}

// go to an angle
// this will only increment - asymptotic
void ServoDrive::goTo(int target) {
    int newAngle = angle + (target-angle)/mood;
    setAngle(newAngle);
}
