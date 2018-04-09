#include <Common.h>
#include <Structs.h>
#include <CameraWrapper.h>
#include <MotorArray.h>
#include <IMU.h>
#include <RotationWrapper.h>
#include <Orbit.h>
#include <Light.h>



/* NOTE Constructors are called in the .cpp file for each class */

void setup(){
    /* Begin Serial */
    Serial.begin(9600);
    /* Init IMU */
    imu.init();
    /* Calibrate IMU for drift etc. */
    imu.calibrate();
    /* Init Serial */
    cam.initSerial();
    /* Init Lightsensors */
    light.init();

}

void loop(){

    /* Get OpenMV7 Data */
    cam.getCamData(ATTACK_YELLOW);

    /* Update IMU */
    imu.update();

    /* Update Light */
    light.readLight();
    light.updateAngle();


    rotation.calculateRotation(imu.getHeading(), 0, 0);
    motors.move(orbitSimple(cam.data.ballAngle, 1), rotation.getRotation(), 20, false);
}
