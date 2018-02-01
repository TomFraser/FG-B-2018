#ifndef MotorArray_h
#define MotorArray_h

#include <Arduino.h>
#include <MotorDriver.h>
#include <Config.h>
#include <Common.h>

class MotorArray {
public:
    MotorArray(MotorDriver a, MotorDriver b, MotorDriver c, MotorDriver d);
    void move(double angle, double rotation, int speed, bool boost);
private:
    int motorAngles[4] = {60, 135, 225, 300};
    double motorSpeeds[4];
};

#endif
