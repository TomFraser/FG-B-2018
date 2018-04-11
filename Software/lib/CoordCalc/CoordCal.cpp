#include <CoordCalc.h>

CoordCalc::CoordCalc(){
  // init
}

/* Public Functions */
void CoordCalc::updateData(cameraData cam, lidarData lidar, double compass_){
    compass = compass_;

    /* Adujust all values for compass reading */
    // camera data
    absCamData absCam;
    absCam.ballAngle = relToAbs(cam.ballAngle);
    absCam.ballDist = calcBallDistCam(cam.ballStrength);
    if(cam.attackingYellow){
        // yellow
        absCam.attackAngle = relToAbs(cam.yGoalAngle);
        absCam.attackDist = calcGoalDistCam(cam.yGoalStrength, true);

        // blue
        absCam.defenceAngle = relToAbs(cam.bGoalAngle);
        absCam.defenceDist = calcGoalDistCam(cam.bGoalStrength, false);

    } else {
        // blue
        absCam.attackAngle = relToAbs(cam.bGoalAngle);
        absCam.attackDist = calcGoalDistCam(cam.bGoalStrength, true);

        // yellow
        absCam.defenceAngle = relToAbs(cam.yGoalAngle);
        absCam.defenceDist = calcGoalDistCam(cam.yGoalStrength, false);
    }

    // lidar data
    lidarData absLidar = {LIDAR_CORRECT_FRONT + relToAbsLidar(lidar.frontDist),
                          LIDAR_CORRECT_BACK + relToAbsLidar(lidar.backDist),
                          LIDAR_CORRECT_LEFT + relToAbsLidar(lidar.leftDist),
                          LIDAR_CORRECT_RIGHT + relToAbsLidar(lidar.rightDist)};


    /* Calculate robot position */
    // caculate an estimate of our position with the camera
    coordinate camCoords = calculateCamCoords(absCam);

    // calculate coordinates based on lidar data
    int leftX = TABLE_LEFT_X - absLidar.leftDist;
    int rightX = TABLE_RIGHT_X + absLidar.rightDist;

    int frontY = TABLE_FRONT_Y - absLidar.frontDist;
    int backY = TABLE_BACK_Y + absLidar.backDist;

    bool leftXverify;
    bool rightXverify;
    bool frontYverify;
    bool backYverify;

    // verify lidar with camera (if we cant see the goal with cam - just assume lidar is correct)
    if(camCoords.x != 65506 && camCoords.y != 65506){
        bool leftXverify = inBaseRange(leftX, camCoords.x, LIDAR_CAM_RANGE);
        bool rightXverify = inBaseRange(rightX, camCoords.x, LIDAR_CAM_RANGE);

        bool frontYverify = inBaseRange(frontY, camCoords.y, LIDAR_CAM_RANGE);
        bool backYverify = inBaseRange(backY, camCoords.y, LIDAR_CAM_RANGE);
    } else {
        leftXverify = true;
        rightXverify = true;
        frontYverify = true;
        backYverify = true;
    }

    // calulate final x
    if(leftXverify && rightXverify){
        // take the smaller lidar distance (cause its likely to be more accurate)
        if (absLidar.leftDist < absLidar.rightDist){
            robot.x = leftX;
        } else {
            robot.x = rightX;
        }
    } else if (leftXverify) {
        robot.x = leftX;
    } else if (rightXverify) {
        robot.x = rightX;
    } else {
        robot.x = camCoords.x;
    }

    // calulate final y
    if(frontYverify && backYverify){
        // take the smaller lidar distance (cause its likely to be more accurate)
        if (absLidar.frontDist < absLidar.backDist){
            robot.y = frontY;
        } else {
            robot.y = backY;
        }
    } else if (frontYverify) {
        robot.y = frontY;
    } else if (backYverify) {
        robot.y = backY;
    } else {
        robot.y = camCoords.y;
    }

    /* Calculate ball position */
    if(absCam.ballAngle != 65506){
        ball.x = robot.x + absCam.ballDist*sin(angToRad*absCam.ballDist);
        ball.y = robot.y + absCam.ballDist*cos(angToRad*absCam.ballDist);
    } else {
        ball.x = 65506;
        ball.y = 65506;
    }
}


/* Private Functions */
int CoordCalc::relToAbs(int relativeDirection){
  return relativeDirection != 65506 ? doubleMod(relativeDirection - compass, 360.0) : 65506;
}

int CoordCalc::absToRel(int absoluteDirection){
  return absoluteDirection != 65506 ? doubleMod(absoluteDirection + compass, 360.0) : 65506;
}

uint16_t CoordCalc::relToAbsLidar(uint16_t value){
    return value * cos(abs(compass)*angToRad);
}

int CoordCalc::calcBallDistCam(int ballStrength){
    // DANK
    // gotta figure out an algorithm for this
    if(ballStrength > 15 && ballStrength < 122){
        return -sqrt(9550-pow(ballStrength-15, 2))+98;
    } else {
        return -1;
    }
}

int CoordCalc::calcGoalDistCam(int goalArea, bool attack){
    // DANK
    #if ROBOT
    // o_bot
    if(goalArea > 105 && goalArea <= 206){
      return -sqrt(9100-0.87*pow(goalArea-105, 2))+101;
    }
    else{
      return -1;
    }
    #else
    // p2_bot
    if(attack){
      // front thing
      if(goalArea > 99 && goalArea <= 198){
        return -1.02*sqrt(10400-1.06*pow(goalArea-99, 2))+111;
      }
      else{
        return -1;
      }
    }
    else{
      // back thing
      if(goalArea > 103 && goalArea <= 214){
        return -sqrt(9100-0.76*pow(goalArea-105, 2))+99;
      }
      else{
        return -1;
      }

    }
    #endif
}

coordinate CoordCalc::calculateCamCoords(absCamData cam){

    coordinate returnCoord;

    int xAttack;
    int yAttack;
    int xDefense;
    int yDefense;

    //65506 is the 'no goal' angle
    bool attackGoal = (cam.attackAngle != 65506);
    bool defenseGoal = (cam.defenceAngle != 65506);

    // attack calulations
    if(attackGoal){

      if(cam.attackDist < 150 && cam.attackDist > 0)
      {
        int xGoal = cam.attackDist*sin(angToRad*cam.attackAngle);
        int yGoal = cam.attackDist*cos(angToRad*cam.attackAngle);

        xAttack = ATTACK_GOAL_X-xGoal;
        yAttack = ATTACK_GOAL_Y-yGoal;

      }
      else{
        attackGoal = false;
      }

    }

    // defense calulations
    if(defenseGoal){
      if(cam.defenceDist < 150 && cam.defenceDist > 0)
      {
        int xGoal = cam.defenceDist*sin(angToRad*cam.defenceAngle);
        int yGoal = cam.defenceDist*cos(angToRad*cam.defenceAngle);

        xDefense = DEFENSE_GOAL_X-xGoal;
        yDefense = DEFENSE_GOAL_Y-yGoal;
      }
      else{
        defenseGoal = false;
      }
    }

    if(attackGoal && defenseGoal){
      // we can see both goals - take the closer goal
      if(cam.attackDist < cam.defenceDist){
        returnCoord.x = xAttack;
        returnCoord.y = yAttack;
      }
      else{
        returnCoord.x = xDefense;
        returnCoord.y = yDefense;
      }

    }
    else if(attackGoal){
      // only attack goal can be seen
      returnCoord.x = xAttack;
      returnCoord.y = yAttack;
    }
    else if(defenseGoal){
      // only defenseGoal can be seen
      returnCoord.x = xDefense;
      returnCoord.y = yDefense;
    }
    else{
      // no goals
      returnCoord.x = 65506;
      returnCoord.y = 65506;
    }

    return returnCoord;

}
