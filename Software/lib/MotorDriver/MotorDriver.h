#ifndef MotorDriver_h
#define MotorDriver_h

#include <Arduino.h>

class MotorDriver {
public:
    MotorDriver(int pwm, int dir, int brk, int rev);
    void set(int pwm);
    void brake();
private:
    int r_brk;
    int r_pwm;
    int r_dir;
    int reversed;

};

#endif
