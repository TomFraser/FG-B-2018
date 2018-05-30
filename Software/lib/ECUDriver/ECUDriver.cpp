#include <ECUDriver.h>

ECUDriver::ECUDriver(int pin){
    motor.attach(pin);
    delay(1000);
    motor.writeMicroseconds(1000);
    delay(1000);
}

/* Dont use this! */
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
