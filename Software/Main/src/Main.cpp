#include <SPIWrapper.h>
#include <MotorArray.h>
#include <Common.h>
#include <Orbit.h>
#include <I2CWrapper.h>
#include <IMU.h>
#include <RotationWrapper.h>
#include <BallManager.h>
#include <SPI.h>

MotorArray motors = MotorArray();
SPIWrapper spi = SPIWrapper();
I2CWrapper i2c = I2CWrapper();
IMU imu = IMU();

void setup(){
    /* Setups */
    spi.initSPI();
    imu.init();
    imu.calibrate();
}

void loop(){
    /* Update Data Data */
    spi.getCamData();
    spi.getIRData();
    imu.update();
}
