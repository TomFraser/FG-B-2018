#include <ECUDriver.h>

ECUDriver::ECUDriver(int pin){
    delay(100);
    motor.attach(pin);
    motor.write(179);
    delay(100);
    motor.write(-179);
    delay(100);
    motor.write(0);
    delay(100);
}

void ECUDriver::setSpeed(solenoidMode mode){
    switch(mode){
        case noSpeed:
            speed = 0;
        case lowSpeed:
            speed = 10;
        case highSpeed:
            speed = 20;
        case hasBall:
            speed = 20;
        case canKick:
            speed = 20;
    }
    motor.write(speed);
}

void ECUDriver::setSpeed(int speed){
    motor.writeMicroseconds(1000 + 10*speed);
}
