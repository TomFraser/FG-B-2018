#ifndef MotorArray_h
#define MotorArray_h

#include <Arduino.h>
#include <MotorDriver.h>
#include <Common.h>

class MotorArray {
public:
    MotorArray();
    void move(double angle, double rotation, int speed, bool boost);
private:
    int motorAngles[4] = {60, 135, 225, 300};
    double motorSpeeds[4];
    double doubleAbs(double value);
    int sign(double value);
    double scale = 0.00;

    /* PWM , DIR, BRK, REV */
    MotorDriver motorA = MotorDriver(2,7,24,1);
    MotorDriver motorB = MotorDriver(3,8,25,1);
    MotorDriver motorC = MotorDriver(4,9,26,0);
    MotorDriver motorD = MotorDriver(5,10,27,0);
};

extern MotorArray motors;

#endif
