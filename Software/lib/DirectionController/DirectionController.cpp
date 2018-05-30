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
    lidar = adjustLidar(lidar_);

    /* Calculate Coordinates of Ball and Robot */
    coordCalc.updateData(cam, lidar);
    myBallCoord = coordCalc.ball;
    myRobotCoord = coordCalc.robot;

    // orbit
    moveAngle = relToAbs(orbit(cam_.ballAngle, cam.ballDist));
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
    xbeeData returnData = {
        myBallCoord,
        myRobotCoord,
        myBallCoord.x != 65506 && myBallCoord.y != 65506,
        myRobotCoord.x != 65506 && myRobotCoord.y != 65506
    };
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

lidarData DirectionController::adjustLidar(lidarData lidar){
    lidarData returnData;
    uint16_t relFront = LIDAR_CORRECT_FRONT + relToAbsLidar(lidar.frontDist);
    uint16_t relBack = LIDAR_CORRECT_BACK + relToAbsLidar(lidar.backDist);
    uint16_t relLeft = LIDAR_CORRECT_LEFT + relToAbsLidar(lidar.leftDist);
    uint16_t relRight = LIDAR_CORRECT_RIGHT + relToAbsLidar(lidar.rightDist);

    if(abs(compass) <= 45){
        returnData.frontDist = relFront;
        returnData.backDist = relBack;
        returnData.leftDist = relLeft;
        returnData.rightDist = relRight;
    } else if(abs(compass) >= 135){
        returnData.frontDist = relBack;
        returnData.backDist = relFront;
        returnData.leftDist = relRight;
        returnData.rightDist = relLeft;
    } else {
        returnData.frontDist = 65506;
        returnData.backDist = 65506;
        returnData.leftDist = 65506;
        returnData.rightDist = 65006;
    }
    return returnData;
}

moveControl DirectionController::calculateReturn(moveControl tempControl){
    // make sure we dont go over the line
    lightTracker.update(light.angle, tempControl.direction, tempControl.speed, cam.ballAngle, light.numSensors);

    // set up the return data struct (WITH LIGHT)
    return {absToRel(lightTracker.getDirection()),
            lightTracker.getSpeed(),
            tempControl.doBoost && lightTracker.getNormalGameplay(),
            rotationPID.update(compass, tempControl.rotation, 0.00)};
}

moveControl DirectionController::goToCoords(coordinate target){
    moveControl moveReturn = {65506,
                              0,
                              false,
                              0};

    if(myRobotCoord.x == 65506 || myRobotCoord.y == 65506){
        // we dunno whats going on -> just stop
        moveReturn.direction = 65506;
        moveReturn.speed = 0;
    } else {
        // we know where we are! go for it
        coordinate delta = {target.x - myRobotCoord.x, target.y - myRobotCoord.y};
        int distance = (int)sqrt(pow(delta.x, 2) + pow(delta.y, 2));

    }
}

// play modes
moveControl DirectionController::calculateAttack(){
    moveControl tempControl;
    if(moveAngle != 65506){
        // if we know where the ball is -> go to it
        tempControl.direction = moveAngle;
        tempControl.speed = SPEED_VAL;
        tempControl.doBoost = true;
        tempControl.rotation = 0; // rotation target
        if(cam.attackAngle != 65506){
            // tempControl.rotation = (360 - absToRel(cam.attackAngle));
            tempControl.rotation = 0;
        }else{
            tempControl.rotation = 0;
        }
        isSpiral = false;
        ballLocation = cam.ballAngle;

        // BACKSPIN LOGIC CAN GO HERE TOO (also goal tracking)
    } else {
        if(!SUPERTEAM){
            /* Normal Game */
            tempControl.direction = moveAngle;
            tempControl.speed = SPEED_VAL;
            tempControl.doBoost = false;
            tempControl.rotation = 0;
        }else{
            /* Big Boi Field! */
            return calculateSpiral(ballLocation);
        }
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

    ballAngle = ballAngle != 65506 ? doubleMod(ballAngle+180, 360)-180 : 65506;

    double horVector;
    if(ballAngle != 65506){
        horVector = goalieAnglePID.update(ballAngle, 0.00, 0.00);
    } else {
        // cant see the ball at all -> center with left and right sonars
        double lidarDiff = lidar.rightDist - lidar.leftDist;
        lidarDiff = abs(lidarDiff) < 2 ? 0 : lidarDiff;
        horVector = goalieSonarPID.update(lidarDiff, 0.00, 0.00);
    }

    double vertVector = -goalieVerPID.update(lidar.backDist, GOALIE_DISTANCE, 0.00);

    double direction = atan2(vertVector, horVector)*radToAng;
    double speed = sqrt(vertVector*vertVector + horVector*horVector);

    direction = doubleMod(direction + 90, 360);

    moveControl returnControl = {
        direction,
        speed,
        false,
        0
    };
    return returnControl;
}

moveControl DirectionController::calculateSpiral(double target){
    if(!isSpiral){
        initialSpiralTime = millis();
        spiralDirection = 0;
    }else{
        /* Spiral has been occuring */
    }
    /* Spiral More towards last direction of ball and less from oppo last dir */
    if(target != 65506){
        goingDirection = smallestAngleBetween(target, spiralDirection) < 1;
        goingOpposite = abs(smallestAngleBetween(target, spiralDirection)-180) < 45;
    }else{
        /* We don't know where the ball is */
        goingDirection = false;
        goingOpposite = false;
    }

    if(goingDirection){
        /* Towards last Ball */
        spiralAdd = 1000/(millis() - initialSpiralTime + SPIRAL_CONST) * SPIRAL_DIRECION_RATE;
    }else if(goingOpposite){
        /* Opposite last Ball */
        spiralAdd = 1000/(millis() - initialSpiralTime + SPIRAL_CONST) * (1/SPIRAL_DIRECION_RATE);
    }else{
        /* Normal Spiral */
        spiralAdd = 1000/(millis() - initialSpiralTime + SPIRAL_CONST) * SPIRAL_RATE;
    }

    spiralDirection = doubleMod(spiralDirection + spiralAdd, 360.0);
    return {spiralDirection, SPIRAL_SPEED ,false, 0};
}