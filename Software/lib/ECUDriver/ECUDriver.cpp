#include <ECUDriver.h>

ECUDriver::ECUDriver(int pin){
    motor.attach(pin);
}

void ECUDriver::setSpeed(solenoidMode mode){
    switch(mode){
        case noSpeed:
            speed = 0;
        case lowSpeed:
            speed = 30;
        case highSpeed:
            speed = 100;
        case hasBall:
            speed = 100;
        case canKick:
            speed = 100;
    }
    motor.writeMicroseconds(map(speed, 0, 100, 700, 2000));
}

/* void ECUDriver::setECUOption(ECUDriverOption option){
     // IDK how to do
 } */
