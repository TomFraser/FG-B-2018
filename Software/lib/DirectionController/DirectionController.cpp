#include <DirectionController.h>

DirectionController dc = DirectionController();

/* Public Functions */

// takes in all structs and data
void DirectionController::updateData(cameraData cam_, lidarData lidar_, lightData light_, xbeeData xbee_, double compass_){
    cam = cam_;
    lidar = lidar_;
    light = light_;
    xbee = xbee_;
    compass = compass_;
    moveAngle = getOrbit(cam.ballAngle);

    /* Calculate Coordinates of Ball and Robot */
    coordCalc.updateData(cam, lidar, compass);
    myBallCoord = coordCalc.ball;
    myRobotCoord = coordCalc.robot;

    Serial.print(myRobotCoord.x); Serial.print(" "); Serial.println(myRobotCoord.y);

}

moveControl DirectionController::calculate(mode robotMode){

    if(robotMode == mode::attacker){
        return calculateAttack();
    }else if(robotMode == mode::defender){
        return calculateGoalie();
    }else{
        return calculateAttack();
    }
}

xbeeData DirectionController::getXbeeData(){
    xbeeData returnData = {myBallCoord,
                           myRobotCoord,
                           myBallCoord.x != 65506 && myBallCoord.y != 65506,
                           myRobotCoord.x != 65506 && myRobotCoord.y != 65506};
    return returnData;
}

/* Private Functions */

// utility functions
double DirectionController::relToAbs(double relativeDirection){
  return relativeDirection != 65506 ? doubleMod(relativeDirection - compass, 360.0) : 65506;
}

double DirectionController::absToRel(double absoluteDirection){
  return absoluteDirection != 65506 ? doubleMod(absoluteDirection + compass, 360.0) : 65506;
}

double DirectionController::getOrbit(double direction){
    // a function that will return the correct orbit that the robot is running
    return direction;
}

// play modes
moveControl DirectionController::calculateAttack(){
    moveControl tempControl;
    if(moveAngle != 65506){
        // if we know where the ball is -> go to it
        tempControl.direction = relToAbs(moveAngle);
        tempControl.speed = SPEED_VAL;
        tempControl.doBoost = true;

        // BACKSPIN LOGIC CAN GO HERE TOO
    } else {
        // cant see ball -> go to other ball coords or predefined ones
        // (or do a spiral for superteam)
    }

    // make sure we dont go over the line
    lightTracker.update(relToAbs(light.angle), tempControl.direction, tempControl.speed, relToAbs(cam.ballAngle), light.numSensors);

    rotation.calculateRotation(compass, cam.attackingYellow == true ? cam.yGoalAngle : cam.bGoalAngle, cam.attackingYellow == true ? cam.yGoalStrength : cam.bGoalStrength, 0.00);
    // set up the return data struct
    moveControl moveReturn = {absToRel(lightTracker.getDirection()),
                              lightTracker.getSpeed(),
                              tempControl.doBoost && lightTracker.getNormalGameplay(),
                              rotation.getRotation()};

    return moveReturn;
}

moveControl DirectionController::calculateGoalie(){

}
