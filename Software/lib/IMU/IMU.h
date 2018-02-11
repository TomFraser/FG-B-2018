#ifndef IMU_h
#define IMU_h

#include <Arduino.h>
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
    double convertRawGyro(int16_t raw) {
        return (raw * 500.0) / 32768.0;
    }
    I2CWrapper I2C = I2CWrapper();
};

extern IMU imu;



#endif
