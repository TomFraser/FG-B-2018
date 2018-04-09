#include <Common.h>
#include <Structs.h>
#include <CameraWrapper.h>


/* #define dc directionController */

/* NOTE Constructors are called in the .cpp file for each class */

// DirectionController directionController = DirectionController();

void setup(){
    /* Begin Serial */
    Serial.begin(9600);
    cam.initSerial();
}

void loop(){

    /* Get OpenMV7 Data */
    cam.getCamData();
    /* Get IR Data from ATMega */
    spi.getIRData();
    /* Update IMU */
    imu.update();

    /* Update Light */
    light.readLight();
    light.updateAngle();

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

    Serial.println(cam.data.ballAngle);

    rotation.calculateRotation(-imu.getHeading(), 0, 0);
    motors.move(orbitSimple(cam.data.ballAngle, 1), rotation.getRotation(), 50, false);

}
