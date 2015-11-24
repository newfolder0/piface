#ifndef SERVO_DRIVE
#define SERVO_DRIVE

#include <Servo.h>

class ServoDrive {
    private:
        int pinX;
        int pinY;
        int angleX;
        int angleY;
        int targetX;
        int targetY;
        int mood;

        Servo servoX;
        Servo servoY;

        ServoDrive() { } // private default constructor

    public:
        // constructors
        ServoDrive(int newPinX, int newPinY);
        ServoDrive(int newPinX, int newPinY, int mood);

        // variable setters
        void setPins(int newPinX, int newPinY);
        void setMood(int mood);
        void setAngles(int newX, int newY);
        void setTargets(int newX, int newY);

        // variable getters
        int getPinX() { return pinX; }
        int getPinY() { return pinY; }
        int getMood() { return mood; }
        // int getAngle() { return angle; }
        // int getTarget() { return targetAngle; }

        // functions
        void update();
};

#endif
