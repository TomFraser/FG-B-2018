#include <DirectionController.h>

DirectionController dc = DirectionController();

/* Public Functions */

// takes in all structs and data
void DirectionController::updateData(cameraData cam_, lidarData lidar_, lightData light_, xbeeData xbee_, double compass_){
    compass = compass_;

    /* Adujust all values for compass reading */

    // light
    light.angle = relToAbs(light_.angle);
    light.numSensors = light_.numSensors;

    // orbit
    moveAngle = relToAbs(getOrbit(cam.ballAngle));

    // xbee data from other robot
    xbee = xbee_;

    // camera data
    cam.ballAngle = relToAbs(cam_.ballAngle);
    cam.ballDist = strengthToDistance(cam_.ballStrength);
    if(cam_.attackingYellow){
        // yellow
        cam.attackAngle = relToAbs(cam_.yGoalAngle);
        cam.attackDist = strengthToDistance(cam_.yGoalStrength);

        // blue
        cam.defenceAngle = relToAbs(cam_.bGoalAngle);
        cam.defenceDist = strengthToDistance(cam_.bGoalStrength);

    } else {
        // blue
        cam.attackAngle = relToAbs(cam_.bGoalAngle);
        cam.attackDist = strengthToDistance(cam_.bGoalStrength);

        // yellow
        cam.defenceAngle = relToAbs(cam_.yGoalAngle);
        cam.defenceDist = strengthToDistance(cam_.yGoalStrength);
    }

    // lidar data
    lidarData lidar = adjustLidar(lidar_);
    // Serial.print(lidar.frontDist); Serial.print(" "); Serial.print(lidar.backDist); Serial.print(" "); Serial.print(lidar.leftDist); Serial.print(" "); Serial.println(lidar.rightDist);


    /* Calculate Coordinates of Ball and Robot */
    coordCalc.updateData(cam, lidar);
    myBallCoord = coordCalc.ball;
    myRobotCoord = coordCalc.robot;

    Serial.print(myRobotCoord.x); Serial.print(" "); Serial.println(myRobotCoord.y);

}

moveControl DirectionController::calculate(mode robotMode){

    if(robotMode == mode::attacker){
        return calculateReturn(calculateAttack());
    }else if(robotMode == mode::defender){
        return calculateReturn(calculateGoalie());
    }else{
        return calculateReturn(calculateAttack());
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

uint16_t DirectionController::relToAbsLidar(uint16_t value){
    return value * cos(abs(compass)*angToRad);
}

double DirectionController::getOrbit(double direction){
    // a function that will return the correct orbit that the robot is running
    return orbitSimple(direction, 1);
}

lidarData DirectionController::adjustLidar(lidarData lidar){
    lidarData returnData;
    uint16_t relFront = LIDAR_CORRECT_FRONT + relToAbsLidar(lidar.frontDist);
    uint16_t relBack = LIDAR_CORRECT_BACK + relToAbsLidar(lidar.backDist);
    uint16_t relLeft = LIDAR_CORRECT_LEFT + relToAbsLidar(lidar.leftDist);
    uint16_t relRight = LIDAR_CORRECT_RIGHT + relToAbsLidar(lidar.rightDist);

    Serial.println(compass);
    if(abs(compass) <= 90-LIDAR_CORRECT_ANGLE){
        returnData.frontDist = relFront;
        returnData.backDist = relBack;
        returnData.leftDist = relLeft;
        returnData.rightDist = relRight;
    } else if(abs(compass) >= 90+LIDAR_CORRECT_ANGLE) {
        returnData.frontDist = relBack;
        returnData.backDist = relLeft;
        returnData.leftDist = relRight;
        returnData.rightDist = relLeft;
    } else if(smallestAngleBetween(compass, 90) < LIDAR_CORRECT_ANGLE){
        returnData.frontDist = relRight;
        returnData.backDist = relLeft;
        returnData.leftDist = relFront;
        returnData.rightDist = relRight;
    } else if(smallestAngleBetween(compass, -90) < LIDAR_CORRECT_ANGLE){
        returnData.frontDist = relLeft;
        returnData.backDist = relRight;
        returnData.leftDist = relBack;
        returnData.rightDist = relFront;
    }

    return returnData;
}

moveControl DirectionController::calculateReturn(moveControl tempControl){
    // make sure we dont go over the line
    lightTracker.update(light.angle, tempControl.direction, tempControl.speed, cam.ballAngle, light.numSensors);

    // set up the return data struct
    moveControl moveReturn = {absToRel(lightTracker.getDirection()),
                              lightTracker.getSpeed(),
                              tempControl.doBoost && lightTracker.getNormalGameplay(),
                              rotationPID.update(compass, tempControl.rotation, 0.00)};
}

// play modes
moveControl DirectionController::calculateAttack(){
    moveControl tempControl;
    if(moveAngle != 65506){
        // if we know where the ball is -> go to it
        tempControl.direction = moveAngle;
        tempControl.speed = SPEED_VAL;
        tempControl.doBoost = true;
        tempControl.rotation = 0;

        // BACKSPIN LOGIC CAN GO HERE TOO (also goal tracking)
    } else {
        // cant see ball -> go to other ball coords or predefined ones
        // (or do a spiral for superteam)
    }

    return tempControl;
}

moveControl DirectionController::calculateGoalie(){
    double ballAngle = 65506;
    if(cam.ballAngle != 65506) {
        ballAngle = cam.ballAngle;
    } else if(xbee.seesBall) {
        ballAngle = atan2(xbee.ballCoords.y - myRobotCoord.y, xbee.ballCoords.x - myRobotCoord.x);
    }

    double horVector;
    if(ballAngle != 65506){
        horVector = goalieAnglePID.update(ballAngle, 0.00, 0.00);
    } else {
        // cant see the ball at all -> center with left and right sonars
        double lidarDiff = lidar.rightDist - lidar.leftDist;
        horVector = goalieSonarPID.update(lidarDiff, 0.00, 0.00);
    }

    double vertVector = goalieVerPID.update(lidar.backDist, GOALIE_DISTANCE, 0.00);

    double direction = atan2(vertVector, horVector);
    double speed = sqrt(vertVector*vertVector + horVector*horVector);

    moveControl returnControl = {direction,
                                 speed,
                                 false,
                                 0};
    return returnControl;

}
