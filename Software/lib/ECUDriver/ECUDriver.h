#ifndef ECUDriver_h
#define ECUDriver_h

#include <Arduino.h>
#include <Servo.h>
#include <Common.h>
#include <Enum.h>

class ECUDriver {
public:
    ECUDriver(int pin);
    void setSpeed(solenoidMode mode);
    /* void setECUOption(ECUDriverOption option); */
private:
    Servo motor;
    int speed;

};

#endif
