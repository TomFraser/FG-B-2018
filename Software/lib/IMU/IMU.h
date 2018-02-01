#ifndef IMU_h
#define IMU_h

#include <Arduino.h>
#include <Config.h>
#include <Common.h>
#include <I2CWrapper.h>

class IMU {
public:
    IMU(){};
    void init();
    double calibrate();
    double read();
    void update();
    double getHeading();
private:
    long currentTime, prevTime;
    double calibration, heading;
    double convertRawGyro(uint16_t raw);
    I2CWrapper I2C = I2CWrapper();


};

#endif
