/*
    header block
 */
// safety stuff
#ifndef MOVEMENT
#define MOVEMENT

#include <Servo.h>

// pin assignments
#define SERVO_X_PIN 9
#define SERVO_Y_PIN 10

// constant config vars
const int X_MAX = 480;
const int Y_MAX = 640;
const int MAX_MOOD = 10;
bool movementInitialised = false;

// set up other vars
Servo servoX, servoY;
int angleX, angleY;

int mood = 0;

// init this whole thing
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
    int speedX = mood*10;
    int speedY = mood*10;

    // translate x and y into angles, make this cleverer - currently linear
    int targetX = (long)newX*180/X_MAX;
    int targetY = (long)newY*180/Y_MAX;

    // safety check of new angles by checking magnitude of change
    int dX = targetX - angleX;
    int dY = targetY - angleY;

    if (abs(dX) < speedX) speedX = abs(dX);
    if (abs(dY) < speedY) speedY = abs(dY);

    // jitter filter thresholds - maybe move out to config vars
    int thresholdLow = 2;
    int thresholdHigh = 180;
    int maxSpeed = 20;

    // speed limiting for safety
    if (speedX > maxSpeed) speedX = maxSpeed;
    if (speedY > maxSpeed) speedY = maxSpeed;

    if (abs(dX) > thresholdLow && abs(dX) < thresholdHigh) {    // filter jitter
        if (dX > 0) angleX = angleX + speedX;
        if (dX < 0) angleX = angleX - speedX;
    }

    if (abs(dY) > thresholdLow && abs(dY) < thresholdHigh) {    // filter jitter
        if (dY > 0) angleY = angleY + speedY;
        if (dY < 0) angleY = angleY - speedY;
    }

    // output to servos
    servoX.write(angleX);
    servoY.write(angleY);

    // print for debugging
    // String str = "Targets: [";
    // str = str + targetX + ", " + targetY + "]";
    // str = str + "\t\tDeltas: [" + dX + ", " + dY + "]";
    // str = str + "\t\tAngles: [" + angleX + ", " + angleY + "]";
    // Serial.println(str);
}

void loopMovement() {
    if (!movementInitialised) initMovement();   // initialise if not already

    int x = faceX;
    int y = faceY;

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
