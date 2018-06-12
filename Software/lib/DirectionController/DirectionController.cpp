#include <DirectionController.h>

DirectionController dc = DirectionController();

/* Public Functions */

DirectionController::DirectionController(){
    // pinMode(KICKER_PIN, OUTPUT);
    // digitalWrite(KICKER_PIN, LOW);
    // timeSinceKick.reset();
    // timeSinceLastKick.reset();
}

void DirectionController::setGoalieDistance(int goalieDistance_){
    goalieDistance = goalieDistance_;
}

// takes in all structs and data
void DirectionController::updateData(cameraData cam_, lidarData lidar_, lightData light_, xbeeData xbee_, double compass_, mode playMode_){
    compass = compass_;

    playMode = playMode_;

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

    // Serial.println(lidar_.backDist);

    // lidar data
    lidar = adjustLidar(lidar_);

    /* Calculate Coordinates of Ball and Robot */
    coordCalc.updateData(cam, lidar, playMode);
    myBallCoord = coordCalc.ball;
    myRobotCoord = coordCalc.robot;

    // update our coord mover object so it knows where we are
    coordMover.update(myRobotCoord, compass);

    // Serial.print(myRobotCoord.x); Serial.print(" "); Serial.println(myRobotCoord.y);
    // Serial.println();
    // Serial.print(myBallCoord.x); Serial.print(" "); Serial.println(myBallCoord.y);
    // Serial.println();
    // Serial.println(cam.defenceAngle);
    // Serial.println(cam_.yGoalStrength);

    // orbit
    moveAngle = relToAbs(orbit(cam_.ballAngle, cam.ballDist));
}

moveControl DirectionController::calculate(){
    controlBall(playMode);
    if(playMode == mode::attacker){
        return calculateReturn(calculateAttack());
    }else if(playMode == mode::defender){
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

uint16_t DirectionController::relToAbsLidar(uint16_t value, double zeroHeading){
    // Serial.print(compass); Serial.print(" "); Serial.println((doubleMod(doubleMod(compass+zeroHeading, 360)+180, 360)-180));
    return value * cos((doubleMod(doubleMod(compass+zeroHeading, 360)+180, 360)-180)*angToRad);
}

lidarData DirectionController::adjustLidar(lidarData lidar){
    lidarData returnData;

    lidar.frontDist = lidar.frontDist > LIDAR_MAX_VALUE ? 65506 : lidar.frontDist;
    lidar.backDist = lidar.backDist > LIDAR_MAX_VALUE ? 65506 : lidar.backDist;
    lidar.leftDist = lidar.leftDist > LIDAR_MAX_VALUE ? 65506 : lidar.leftDist;
    lidar.rightDist = lidar.rightDist > LIDAR_MAX_VALUE ? 65506 : lidar.rightDist;

    // Serial.println(compass);
    // Serial.print(lidar.frontDist); Serial.print(" "); Serial.print(lidar.backDist); Serial.print(" "); Serial.print(lidar.leftDist); Serial.print(" "); Serial.println(lidar.rightDist);
    int zeroHeading;
    if(compass < 0){
        if(compass > -45) {
            // front
            zeroHeading = 0;
        } else if(compass > -135) {
            // left
            zeroHeading = 90;
        } else {
            // back
            zeroHeading = 180;
        }
    } else {
        if(compass < 45) {
            // front
            zeroHeading = 0;
        } else if(compass < 135) {
            // right
            zeroHeading = -90;
        } else {
            // back
            zeroHeading = -180;
        }
    }

    lidar.frontDist = lidar.frontDist == 65506 ? 65506 : LIDAR_CORRECT_FRONT + relToAbsLidar(lidar.frontDist, zeroHeading);
    lidar.backDist = lidar.backDist == 65506 ? 65506 : LIDAR_CORRECT_BACK + relToAbsLidar(lidar.backDist, zeroHeading);
    lidar.leftDist = lidar.leftDist == 65506 ? 65506 : LIDAR_CORRECT_LEFT + relToAbsLidar(lidar.leftDist, zeroHeading);
    lidar.rightDist = lidar.rightDist == 65506 ? 65506 : LIDAR_CORRECT_RIGHT + relToAbsLidar(lidar.rightDist, zeroHeading);

    if(compass < 0){
        if(compass > -45) {
            // front
            returnData.frontDist = lidar.frontDist;
            returnData.backDist = lidar.backDist;
            returnData.leftDist = lidar.leftDist;
            returnData.rightDist = lidar.rightDist;
        } else if(compass > -135) {
            // left
            returnData.frontDist = lidar.rightDist;
            returnData.backDist = lidar.leftDist;
            returnData.leftDist = lidar.frontDist;
            returnData.rightDist = lidar.backDist;
        } else {
            // back
            returnData.frontDist = lidar.backDist;
            returnData.backDist = lidar.frontDist;
            returnData.leftDist = lidar.rightDist;
            returnData.rightDist = lidar.leftDist;
        }
    } else {
        if(compass < 45) {
            // front
            returnData.frontDist = lidar.frontDist;
            returnData.backDist = lidar.backDist;
            returnData.leftDist = lidar.leftDist;
            returnData.rightDist = lidar.rightDist;
        } else if(compass < 135) {
            // right
            returnData.frontDist = lidar.leftDist;
            returnData.backDist = lidar.rightDist;
            returnData.leftDist = lidar.backDist;
            returnData.rightDist = lidar.frontDist;
        } else {
            // back
            returnData.frontDist = lidar.backDist;
            returnData.backDist = lidar.frontDist;
            returnData.leftDist = lidar.rightDist;
            returnData.rightDist = lidar.leftDist;
        }
    }


    // Serial.print(returnData.frontDist); Serial.print(" "); Serial.print(returnData.backDist); Serial.print(" "); Serial.print(returnData.leftDist); Serial.print(" "); Serial.println(returnData.rightDist);
    // Serial.println();
    return returnData;
}

moveControl DirectionController::calculateReturn(moveControl tempControl){
    // make sure we dont go over the line
    lightTracker.update(light.angle, tempControl.direction, tempControl.speed, cam.ballAngle, light.numSensors);

    // set up the return data struct (WITH LIGHT)
    // return {absToRel(lightTracker.getDirection()),
    //         lightTracker.getSpeed(),
    //         tempControl.doBoost && lightTracker.getNormalGameplay(),
    //         rotationPID.update(doubleMod(doubleMod(compass-tempControl.rotation, 360)+180, 360)-180, 0.00, 0.00)};

    // set up the return data struct (NO LIGHT)
    return {absToRel(tempControl.direction),
            tempControl.speed,
            tempControl.doBoost,
            rotationPID.update(doubleMod(doubleMod(compass-tempControl.rotation, 360)+180, 360)-180, 0.00, 0.00)};
}

// play modes
moveControl DirectionController::calculateAttack(){
    moveControl tempControl;
    // if(false){
    if(moveAngle != 65506){
        // if we know where the ball is -> go to it
        tempControl.direction = moveAngle;
        tempControl.speed = SPEED_VAL;
        tempControl.doBoost = true;
        if(cam.attackAngle != 65506){
            tempControl.rotation = -cam.attackAngle;
        } else {
            // 'goal track' based on our coordinates
            // double deltaY = ATTACK_GOAL_Y - myRobotCoord.y;
            // double deltaX = ATTACK_GOAL_X - myRobotCoord.x;
            // double angle = atan2(deltaY, deltaX);
            // tempControl.rotation = fromFront(mod(angle * radToAng - 90, 360));
            tempControl.rotation = 0;
        }

        isSpiral = false;
        ballLocation = cam.ballAngle;

        // BACKSPIN LOGIC CAN GO HERE
    } else {
        // dont know where the ball is -> do other strategies
        if(!SUPERTEAM){
            /* Normal Game */
            // TODO: write some proper strategies in here (add in xbee strats)
            if(coordMover.completed){
                // coordinate targets[] = {{0, -50}, {40, -50}, {40, 0}, {40, 50}, {0, 50}, {0, 70}};
                // int rotationTargets[] = {0, -90, -90, -90, 180, 0};
                coordinate targets[] = {{0,0}};
                int rotationTargets[] = {0};
                coordMover.setTargetList(targets, sizeof(targets)/sizeof(targets[0]), rotationTargets);
            }
            tempControl = coordMover.calcMove();
        }else{
            /* Big Boi Field! */
            tempControl = calculateSpiral(ballLocation);
        }
    }
    // Serial.print(tempControl.direction); Serial.print(" "); Serial.print(tempControl.speed); Serial.print(" "); Serial.println(tempControl.rotation);

    return tempControl;
}

moveControl DirectionController::calculateGoalie(){
    // Serial.print(lidar.backDist); Serial.print(" "); Serial.println(goalieDistance);

    double ballAngle = 65506;
    double ballDist = 65506;
    if(cam.ballAngle != 65506) {
        if((cam.ballAngle > 60 && cam.ballAngle < 300)||((abs(fromFront(cam.ballAngle)) < 5) && cam.ballDist < 100 && myRobotCoord.y < 0)){
            goalieVerPID.update(lidar.backDist, goalieDistance, 0.00);
            return {moveAngle, SPEED_VAL, false, 0};
        }

        ballAngle = cam.ballAngle;
        ballDist = cam.ballDist;
    } else if(xbee.seesBall) {
        ballAngle = mod(atan2(xbee.ballCoords.y - myRobotCoord.y, xbee.ballCoords.x - myRobotCoord.x)*radToAng - 90, 360);
        ballDist = sqrt(pow(xbee.ballCoords.y-myRobotCoord.y, 2) + pow(xbee.ballCoords.x-myRobotCoord.x, 2));
    }

    ballAngle = ballAngle != 65506 ? doubleMod(ballAngle+180, 360)-180 : 65506;

    // Serial.println(ballAngle);

    // Check if we need to yeet back
    // Serial.print(myRobotCoord.y); Serial.print(" "); Serial.println(TABLE_BACK_Y + goalieDistance);
    if(ballAngle == 65506 && myRobotCoord.y > GOALIE_Y){
        return coordMover.goToCoords({0, GOALIE_Y}, 0);
    }

    double horVector = 0;
    if(ballAngle != 65506){
        ballAngle = abs(ballAngle) < 5 ? 0 : ballAngle;
        horVector = goalieAnglePID.update(ballAngle, 0.00, 0.00);
        // Serial.print(horVector); Serial.print(" "); Serial.println(myRobotCoord.x);
        if(horVector < 0){
            if(myRobotCoord.x > GOALIE_X_RANGE+10){
                horVector = GOALIE_AVOID_SPEED;
            } else if(myRobotCoord.x >= GOALIE_X_RANGE){
                horVector = 0;
            }
        } else if(horVector > 0){
            if(myRobotCoord.x < -GOALIE_X_RANGE-10){
                horVector = -GOALIE_AVOID_SPEED;
            } else if(myRobotCoord.x <= -GOALIE_X_RANGE){
                horVector = 0;
            }
        }
        // Serial.println(horVector);
    } else {
        // cant see the ball at all -> center with x coordinate
        if(myRobotCoord.x != 65506){
            horVector = goalieHorPID.update(abs(myRobotCoord.x) < 5 ? 0 : myRobotCoord.x, 0.00, 0.00);
        }
    }

    // test if this still works, and then limit the horVector if the
    // x is ouside the bounds

    double vertVector = 0;
    // Serial.print(lidar.backDist); Serial.print(" "); Serial.println(goalieDistance);
    if(lidar.backDist != 65506){
        vertVector = -goalieVerPID.update(lidar.backDist, goalieDistance, 0.00);
    }

    double direction = atan2(vertVector, horVector)*radToAng;
    double speed = sqrt(vertVector*vertVector + horVector*horVector);

    direction = doubleMod(direction + 90, 360);

    moveControl returnControl = {
        direction,
        speed,
        false,
        0
    };

    // Serial.print(returnControl.direction); Serial.print(" "); Serial.println(returnControl.speed);
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

void DirectionController::controlBall(mode playMode_){
    if(playMode_ == mode::attacker){
        /* Attacking */
        if(abs(fromFront(cam.attackAngle)) < SOLENOID_THRESHOLD && myRobotCoord.y > 15 && abs(fromFront(cam.ballAngle)) <= 10){
            /* We are roughly facing the goal and are in their half of the field */
            kicker.kickBall();
        }
    // }else if(playMode_ == mode::defender){
    //     /* Defending */
    //     if(myRobotCoord.y > -45){
    //         kicker.kickBall();
    //     }
    }
}
