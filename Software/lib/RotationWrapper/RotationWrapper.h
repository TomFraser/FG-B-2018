#ifndef RotationWrapper_h
#define RotationWrapper_h

#include <Arduino.h>
#include <Math.h>
#include <Common.h>
#include <PID.h>

class RotationWrapper {
public:
    RotationWrapper(){};
    void calculateRotation(double rotation, double goal, double goalSize);
    double getRotation();
private:
    double compassHeading, goalHeading, gyration;
    PID IMUController = PID(0.00, 0.00, 0.00, 0.00);
    PID goalController = PID(0.00, 0.00, 0.00, 0.00);
};

extern RotationWrapper rotation;

#endif
