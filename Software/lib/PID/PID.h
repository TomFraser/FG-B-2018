#ifndef PID_h
#define PID_h

#include <Arduino.h>

class PID {
public:
    double kp, ki, kd;

    PID(double p, double i, double d, double absoluteMax = 0.0);
    double update(double input, double setpoint, double modulus = 0.0);
private:
    ulong lastTime;
    double absMax, integral, lastInput;
};

#endif
