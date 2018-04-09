#include <Common.h>
#include <Structs.h>
#include <SPIWrapper.h>
#include <MotorArray.h>
#include <Common.h>
#include <Orbit.h>
#include <IMU.h>
#include <RotationWrapper.h>
// #include <BallManager.h>
#include <CameraWrapper.h>
#include <DirectionController.h>
#include <Light.h>
#include <ModeWrapper.h>
// #include <Xbee.h>


/* NOTE Constructors are called in the .cpp file for each class */

void setup(){
    /* Begin Serial */
    Serial.begin(9600);
    /* Init SPI */
    spi.initSPI();
    /* Init IMU */
    imu.init();
    /* Calibrate IMU for drift etc. */
    imu.calibrate();
    /* Init Lightsensors */
    light.init();
    /* Init Serial */
    cam.initSerial();
    /* Set robot mode based on default mode */
    /*
    if(ROBOT){
        robotMode.setDefault(defender);
    }else{
        robotMode.setDefault(attacker);
    }*/
    pinMode(KICKER_PIN, OUTPUT);
}

void loop(){

    /* Get OpenMV7 Data */
    cam.getCamData(ATTACK_YELLOW);

    /* Get IR Data from ATMega */
    spi.getIRData();
    /* Update IMU */
    imu.update();

    /* Update Light */
    light.readLight();
    light.updateAngle();

    // PLACEHOLDER DATA THAT NEEDS TO BE DONE
    lidarData ldata = {0, 0, 0, 0};
    xbeeData xdata = {{0, 0}, {0, 0}, false, false};



    /* Update Game Data */
    dc.updateData(cam.data, ldata, light.data, xdata, imu.getHeading());

    /* Update Goal Data */
    // #if ATTACK_YELLOW
    //     directionController.updateGoalData(cam._ySize, cam._yAngle, cam._bSize, cam._bAngle);
    // #else
    //     directionController.updateGoalData(cam._bSize, cam._bAngle, cam._ySize, cam._yAngle);
    // #endif

    /* Move based on mode and other data */
    // if(robotMode.getMode() == mode::defender){
        // directionController.calculateGoalie();
        // motors.move(dc.getDirection(), imu.getHeading(), dc.getSpeed(), false);
    // }else{
        // directionController.calculateAttack();
        // motors.move(dc.getDirection(), imu.getHeading(), dc.getSpeed(), dc.getFollowingBall());
    // }

    /* Send and recieve Xbee Data */
    // xbee.updateData(dc.getBallX(), dc.getBallY(), dc.getX(), dc.getY(), dc.getFollowingBall(), dc.getBallX() != 65506 ? 1 : 0);

    /* Update other robots data to direction Controller */
    // directionController.updateOtherData(xbee.OballX, xbee.OballY, xbee.OrobotX, xbee.OrobotY, xbee.OseeingBall == 1 ? true : false, xbee.OknowsPosition == 1 ? true : false);

    Serial.println(cam.data.ballAngle);

    rotation.calculateRotation(-imu.getHeading(), 0, 0);
    motors.move(orbitSimple(cam.data.ballAngle, 1), rotation.getRotation(), 50, false);

}
