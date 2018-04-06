#include <DirectionController.h>

DirectionController dc = DirectionController();

/* Public Functions */

void DirectionController::attackingYellow(bool attackYellow_){
    attackYellow = attackYellow_;
}

// takes in all structs and data
void DirectionController::updateData(cameraData cam_, lidarData lidar_, lightData light_, xbeeData xbee_, double compass_){
    cam = cam_;
    lidar = lidar_;
    light = light_;
    xbee = xbee_;
    compass = compass_;
    moveAngle = getOrbit(cam.ballAngle);

    // TODO
    /* Calculate Coordinates of Ball and Robot */
    // coordCalc.updateData(cam, lidar, compass);
    // ballCoord = coordCalc.ball;
    // robotCoord = coordCalc.robot;


}

moveControl DirectionController::calculate(bool attack){
    if(attack){
        return calculateAttack();
    } else {
        return calculateGoalie();
    }
}

xbeeData getXbeeData(){

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
    if(cam.ballAngle != 65506){
        lightTracker.update(relToAbs(light.angle), relToAbs(moveAngle), SPEED_VAL, relToAbs(cam.ballAngle), light.numSensors);

        // set up the return data struct
        moveControl moveReturn;
        moveReturn.direction = absToRel(lightTracker.getDirection());
        moveReturn.speed = lightTracker.getSpeed();
        moveReturn.doBoost = lightTracker.getNormalGameplay();

        return moveReturn;

        // BACKSPIN LOGIC CAN GO HERE TOO
    } else {
        // cant see ball -> go to other ball coords or predefined ones
        // (or do a spiral for superteam)
    }
}

moveControl DirectionController::calculateGoalie(){

}
