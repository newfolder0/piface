/*
    header block
 */
// safety stuff
#ifndef MOVEMENT
#define MOVEMENT

#include <Servo.h>

// pin assignments
#define SERVO_X_PIN 8
#define SERVO_Y_PIN 9

// constant config vars
const int X_MAX = 480;
const int Y_MAX = 640;
const int MAX_MOOD = 10;
const int MAX_DELTA_ANGLE = 5;
bool movementInitialised = false;

// set up other vars
Servo servoX, servoY;
int angleX, angleY;

int mood = 0;

void initMovement() {
    servoX.attach(SERVO_X_PIN);
    servoY.attach(SERVO_Y_PIN);

    angleX = 90;
    angleY = 90;

    servoX.write(angleX);
    servoY.write(angleY);

    movementInitialised = true;
}

void pointEye(int newX, int newY) {
    // translate x and y into angles, make this cleverer - currently linear
    int newAngleX = (long)newX*90/X_MAX;
    int newAngleY = (long)newY*90/Y_MAX;

    String str = "[";
    Serial.println(str + newAngleX + ", " + newAngleY + "]");

    // safety check of new angles by checking magnitude of change
    int dX = newAngleX - angleX;
    int dY = newAngleY - angleY;

    // set new X angle
    if (dX > MAX_DELTA_ANGLE) angleX = angleX + dX;
    else if (dX < 0-MAX_DELTA_ANGLE) angleX = angleX - dX;
    else angleX = newAngleX;

    // set new Y angle
    if (dY > MAX_DELTA_ANGLE) angleY = angleY + dY;
    else if (dY < 0-MAX_DELTA_ANGLE) angleY = angleY - dY;
    else angleY = newAngleY;

    // output to servos
    servoX.write(angleX);
    servoY.write(angleY);
}

void loopMovement() {
    if (!movementInitialised) initMovement();   // initialise if not already

    int x = data[0];
    int y = data[1];

    switch (mood) {
        case 0: //  dormant
            servoX.write(90);
            servoY.write(90);
            break;

        case 1: // start of movement cases
            pointEye(x, y);

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
        case 6:

            break;
        case 7:

            break;
        case 8:

            break;
        case 9:

            break;
        case 10: // stressed, go nuts

            break;
        default:    // default state, centre both servos
            servoX.write(90);
            servoX.write(90);
            break;
    }
}

#endif
