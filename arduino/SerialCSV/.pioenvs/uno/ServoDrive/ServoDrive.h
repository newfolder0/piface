#ifndef SERVO_DRIVE
#define SERVO_DRIVE

class ServoDrive
{
private:
    int angle;
    int servoPin;
    int mood;

    ServoDrive() { } // private default constructor

public:
    // constructors
    ServoDrive(int newPin);
    ServoDrive(int newPin, int newAngle, int mood);

    // variable setters
    void setAngle(int newAngle);
    void setPin(int newPin);
    void setMood(int mood);

    // variable getters
    int getAngle() { return angle; }
    int getPin() { return servoPin; }
    int getMood() { return mood; }

    // functions
    void goTo(int target);
};

#endif
