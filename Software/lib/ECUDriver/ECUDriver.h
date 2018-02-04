#ifndef ECUDriver_h
#define ECUDriver_h

#include <Arduino.h>
#include <Servo.h>
#include <Common.h>

class ECUDriver {
public:
    ECUDriver(int pin);
    void setSpeed(int speed);
    void setECUOption(ECUDriverOption option);
private:
    Servo motor;

};

#endif
