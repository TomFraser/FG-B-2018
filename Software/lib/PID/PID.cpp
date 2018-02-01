#include <PID.h>

PID::PID(double p, double i, double d, double absoluteMax){
    kp = p;
    ki = i;
    kd = d;
    absMax = absoluteMax;

    lastTime = micros();
}

double PID::update(double input, double setpoint, double modulus){
    double derivative;
    double error = setpoint - input;

    ulong currentTime = micros();
    double elapsedTime = (currentTime - lastTime) / 1000000.0;
    lastTime = currentTime;
    integral += elapsedTime * error;
    if(modulus != 0.0){
        double difference = (input - lastInput);
        if(difference < -modulus){
            difference += modulus;
        }else if(difference > modulus) {
            difference -= modulus;
        }
        derivative = difference / elapsedTime;
    }else{
        derivative = (input - lastInput) / elapsedTime;
    }
    lastInput = input;
    double correction = kp * error + ki * integral - kd * derivative;
    return absMax == 0 ? correction : constrain(correction, -absMax, absMax);
}
