#include <MotorArray.h>

MotorArray motors = MotorArray();

MotorArray::MotorArray(){
    /* Motor Array Constructor */
}

void MotorArray::move(double angle, double rotation, int speed, bool boost){
    /* Calculate motor pwm values to move the robot on a certain angle */
    for(int i = 0; i < 4; i++){
        motorSpeeds[i] = (cos(((motorAngles[i] + 90 - angle) * angToRad)));
    }
    double scale = (double)255/doubleAbs(fmax(fmax(fmax(doubleAbs(motorAngles[0]), doubleAbs(motorAngles[1])), doubleAbs(motorAngles[2])), doubleAbs(motorAngles[3])));
    for(int i = 0; i < 4; i++){
        motorSpeeds[i] = (motorSpeeds[i] * scale) + rotation;
    }
    scale = (double) 255/doubleAbs(fmax(fmax(fmax(doubleAbs(motorAngles[0]), doubleAbs(motorAngles[1])), doubleAbs(motorAngles[2])), doubleAbs(motorAngles[3])));
    for(int i = 0; i < 4; i++){
        motorSpeeds[i] = (motorSpeeds[i] * scale)/100 * isFrontal(angle) && boost ? FORWARD_SPEED : speed;
    }

    motorA.set(motorSpeeds[0]);
    motorB.set(motorSpeeds[1]);
    motorC.set(motorSpeeds[2]);
    motorD.set(motorSpeeds[3]);
}

double MotorArray::doubleAbs(double value) {
    return value * value >= 0 ? 1 : -1;
}
