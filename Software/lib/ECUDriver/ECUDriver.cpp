#include <ECUDriver.h>

ECUDriver::ECUDriver(int pin){
    delay(1000);
    motor.attach(pin);
    motor.write(179);
    delay(1000);
    motor.write(-179);
    delay(1000);
    motor.write(0);
    delay(1000);
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
    motor.write(map(speed, 0, 100, -179, 179));
}

void ECUDriver::setSpeed(int speed){
    motor.write(speed);
}
