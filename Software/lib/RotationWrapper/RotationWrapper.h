#ifndef RotationWrapper_h
#define RotationWrapper_h

#include <Arduino.h>
#include <Config.h>
#include <Common.h>
#include <PID.h>

class RotationWrapper {
public:
    RotationWrapper(){};
    void calculateRotation(double rotation, double goal, double goalSize);
    double getRotation();
private:
    double compassHeading, goalHeading;
    PID pidController = PID(0.00, 0.00, 0.00, 0.00);
};

#endif
