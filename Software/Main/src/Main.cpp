#include <SPIWrapper.h>
#include <MotorArray.h>
#include <Common.h>
#include <Orbit.h>
#include <IMU.h>
#include <RotationWrapper.h>
#include <BallManager.h>
#include <CameraWrapper.h>
#include <DirectionController.h>
#include <Light.h>
#include <modeWrapper.h>
#include <Xbee.h>

DirectionController directionController = DirectionController();
Light light;
int lightData;
int lightNumData;

/* NOTE Constructors are called in the .cpp file for each class */

void setup(){
    /* Init SPI */
    spi.initSPI();
    /* Init IMU */
    imu.init();
    /* Calibrate IMU for drift etc. */
    imu.calibrate();
    /* Init Lightsensors */
    light.init();
    /* Set robot mode based on default mode */
    if(ROBOT){
        robotMode.setMode(defender);
    }else{
        robotMode.setMode(attacker);
    }
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

    /* Update Light */
    light.readLight();

    /* Update Game Data */
    directionController.updateGameData(cam.rawAngle, cam.rawAngle, cam.strength, light.getAngle(), light.getNumSensors(), imu.getHeading(), robotMode.getMode());

    /* Update Goal Data */
    directionController.updateGoalData(cam._aSize, cam._aAngle, cam._dSize, cam._dAngle);

    /* Move based on mode and other data */
    if(robotMode.getMode() == mode::defender){
        directionController.calculateGoalie();
        motors.move(directionController.getDirection(), imu.getHeading(), directionController.getSpeed(), false);
    }else{
        directionController.calculateAttack();
        motors.move(directionController.getDirection(), imu.getHeading(), directionController.getSpeed(), directionController.getFollowingBall());
    }

    /* Do Xbee and Solenoid stuffs here */
}
