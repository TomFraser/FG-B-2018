#include <CameraWrapper.h>
#include <MotorDriver.h>
#include <Config.h>
#include <Common.h>
#include <Orbit.h>
#include <I2CWrapper.h>
#include <IMU.h>
#include <PID.h>

void setup(){
    pinMode(13, OUTPUT);
}

void loop(){
    digitalWrite(13, HIGH);
    // The order of what we have to do (Based on last year)
    //
    // READ CAMERA DATA (We should develop some way to do this more effeciently)
    // Updating the camera / game data to the robot
    // determining if the robot is in goalie or attacker mode (this includes moving) <-- Should be done at the end
    // Checking lightgate
    // Xbee connection and data transfer
    // That it

    // The new order that we should probs do things this year
    //
    //  READ CAMERA DATA
    //  UPDATE GAME DATA
    //  CHECK ROBOT MODE
    //  CHECK LIGHTGATE
    //  XBEE DATA TRANSFER
    //  MOVE BASED ON ALL THIS INFORMATION

    // TODO:
    //
    // Write camera data transfer library
}
