#include <SPIWrapper.h>
#include <MotorArray.h>
// #include <Common.h>
#include <Orbit.h>
#include <IMU.h>
// #include <RotationWrapper.h>
// #include <BallManager.h>
#include <CameraWrapper.h>
// #include <DirectionController.h>
// #include <Light.h>
// #include <ModeWrapper.h>
// #include <Xbee.h>


/* #define dc directionController */

/* NOTE Constructors are called in the .cpp file for each class */

// DirectionController directionController = DirectionController();
// Light light;
int lightData;
int lightNumData;

void setup(){
    /* Init SPI */
    Serial.begin(9600);
    spi.initSPI();
    /* Init IMU */
    imu.init();
    /* Calibrate IMU for drift etc. */
    imu.calibrate();
    /* Init Lightsensors */
    // light.init();
    /* Init Serial */
    cam.initSerial();
    /* Set robot mode based on default mode */
    // if(ROBOT){
        // robotMode.setDefault(defender);
    // }else{
        // robotMode.setDefault(attacker);
    // }
}

void loop(){

    /* Get OpenMV7 Data */
    cam.getCamData();

    /* Get IR Data from ATMega */
    // spi.getIRData();
    /* Update IMU */
    imu.update();

    /* Testing Orbit Function */
    // orbit(0,0);

    /* Update Light */
    // light.readLight();

    /* Update Game Data */
    // directionController.updateGameData(cam.rawAngle, cam.rawAngle, cam.strength, light.getAngle(), light.getNumSensors(), imu.getHeading(), robotMode.getMode());

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
    // Serial.println(orbitSimple(cam.rawAngle, 1));
    motors.move(orbitSimple(cam.rawAngle, 1), -imu.getHeading(), 50, false);
}
