#include <MotorDriver.h>

MotorDriver::MotorDriver(int pwm, int dir, int brk, int rev){
    /* Motor Constructor */
    pinMode(pwm, OUTPUT);
    pinMode(dir, OUTPUT);
    pinMode(brk, OUTPUT);
    reversed = rev;
    r_pwm = pwm;
    r_dir = dir;
    r_brk = brk;
    analogWriteFrequency(pwm, 800);
}

void MotorDriver::set(int pwm){
    /* Set a pwm value to a motor */
    digitalWrite(r_dir, pwm > 0 ? !reversed : reversed);
    analogWrite(r_pwm, pwm > 0 ? pwm : -pwm);
    digitalWrite(r_brk, LOW);
}

void MotorDriver::brake(){
    /* Force a motor to brake */
    digitalWrite(r_dir, LOW);
    analogWrite(r_pwm, 0);
    digitalWrite(r_brk, HIGH);
}
