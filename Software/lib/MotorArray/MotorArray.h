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

    MotorDriver motorA = MotorDriver(0,0,0,0);
    MotorDriver motorB = MotorDriver(0,0,0,0);
    MotorDriver motorC = MotorDriver(0,0,0,0);
    MotorDriver motorD = MotorDriver(0,0,0,0);
};

extern MotorArray motors;

#endif
