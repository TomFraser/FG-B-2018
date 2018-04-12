#include <Common.h>
#include <Structs.h>
#include <CameraWrapper.h>
#include <MotorArray.h>
#include <IMU.h>
#include <RotationWrapper.h>
#include <Orbit.h>
#include <Light.h>



void setup(){
    /* Begin Serial */
    Serial.begin(9600);

}

void loop(){
    Serial.println("waht");
    Serial.println(smallestAngleBetween(-100, 90));
}
