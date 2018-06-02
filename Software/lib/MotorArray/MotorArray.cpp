#include <MotorArray.h>

MotorArray motors = MotorArray();

MotorArray::MotorArray(){
    /* Motor Array Constructor */
}

void MotorArray::move(moveControl move){
    double angle = move.direction;
    int speed = abs(move.speed);
    bool boost = move.doBoost;
    double rotation = move.rotation;
    /* Calculate motor pwm values to move the robot on a certain angle */
    if(angle != 65506.00){
        for(int i = 0; i < 4; i++){
            motorSpeeds[i] = (cos(((motorAngles[i] + 90 - angle) * angToRad)));
        }
        scale = 255/doubleAbs(fmax(fmax(fmax(doubleAbs(motorSpeeds[0]), doubleAbs(motorSpeeds[1])), doubleAbs(motorSpeeds[2])), doubleAbs(motorSpeeds[3])));
        for(int i = 0; i < 4; i++){
            motorSpeeds[i] = (motorSpeeds[i] * scale) + rotation;
        }
        scale = 255/doubleAbs(fmax(fmax(fmax(doubleAbs(motorSpeeds[0]), doubleAbs(motorSpeeds[1])), doubleAbs(motorSpeeds[2])), doubleAbs(motorSpeeds[3])));
        for(int i = 0; i < 4; i++){
            if(isFrontalLarge(angle) == true && boost == true){
                motorSpeeds[i] = (motorSpeeds[i] * scale)/100 * FORWARD_SPEED;
            }else{
                motorSpeeds[i] = (motorSpeeds[i] * scale)/100 * speed;
            }
        }
    }else{
        for(int i = 0; i < 4; i ++){
            motorSpeeds[i] = rotation;
        }
    }

    motorA.set(motorSpeeds[0]);
    motorB.set(motorSpeeds[1]);
    motorC.set(motorSpeeds[2]);
    motorD.set(motorSpeeds[3]);
}
void MotorArray::sound(long in){
    // analogWriteFrequency(2, in);
    // analogWriteFrequency(3, in);
    // analogWriteFrequency(4, in);
    // analogWriteFrequency(5, in);
    motorA.set(70);
    motorB.set(70);
    motorC.set(70);
    motorD.set(70);
    pirates();
}

int MotorArray::sign(double value) {
    return value >= 0 ? 1 : -1;
}

double MotorArray::doubleAbs(double value) {
    return value * sign(value);
}
