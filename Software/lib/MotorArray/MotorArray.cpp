#include <MotorArray.h>

MotorArray::MotorArray(MotorDriver a, MotorDriver b, MotorDriver c, MotorDriver d){
    /* Motor Array Constructor */
    MotorDriver motorA = a;
    MotorDriver motorB = b;
    MotorDriver motorC = c;
    MotorDriver motorD = d;
}

MotorArray::move(double angle, double rotation, int speed, bool boost){
    /* Calculate motor pwm values to move the robot on a certain angle */
    for(int i = 0; i < 4; i++){
        motorSpeeds[i] = (cos(((motorAngles[i] + 90 - angle) * angToRad)));
    }
    double scale = (double)255/doubleAbs(fmax(fmax(fmax(doubleAbs(motorAPWM), doubleAbs(motorBPWM)), doubleAbs(motorCPWM)), doubleAbs(motorDPWM)));
    for(int i = 0; i < 4; i++){
        motorSpeeds[i] = (motorSpeeds[i] * scale) + rotation;
    }
    scale = (double) 255/doubleAbs(fmax(fmax(fmax(doubleAbs(motorASpeed), doubleAbs(motorBSpeed)), doubleAbs(motorCSpeed)), doubleAbs(motorDSpeed)));
    for(int i = 0; i < 4; i++){
        motorSpeeds[i] = (motorSpeeds[i] * scale)/100 * isFrontal(angle) && boost ? FORWARD_SPEED : speed;
    }
}
