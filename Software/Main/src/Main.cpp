#include <SPIWrapper.h>
#include <MotorArray.h>
#include <Common.h>
#include <Orbit.h>
#include <IMU.h>
#include <RotationWrapper.h>
#include <BallManager.h>
#include <CameraWrapper.h>

/* NOTE Constructors are called in the .cpp file for each class */

void setup(){
    /* Init SPI */
    spi.initSPI();
    /* Init IMU */
    imu.init();
    /* Calibrate IMU for drift etc. */
    imu.calibrate();
}

void loop(){
    /* Get OpenMV7 Data */
    cam.getCamData();
    /* Get IR Data from ATMega */
    spi.getIRData();
    /* Update IMU */
    imu.update();
    /* Testing Orbit Function */
    orbit(0,0);
}
