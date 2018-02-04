#include <ECUDriver.h>

ECUDriver::ECUDriver(int pin){
    motor.attach(pin);
}

void ECUDriver::setSpeed(int speed){
    motor.writeMicroseconds(map(speed, 0, 100, 700, 2000));
}

void ECUDriver::setECUOption(ECUDriverOption option){
    // IDK how to do
}
