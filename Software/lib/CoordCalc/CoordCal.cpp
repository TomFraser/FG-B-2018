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
    lidarData absLidar = {relToAbsLidar(lidar.frontDist),
                          relToAbsLidar(lidar.backDist),
                          relToAbsLidar(lidar.leftDist),
                          relToAbsLidar(lidar.rightDist)};


    /* Calculate robot position */
    // calulate a quadrant we're in
        // 1. use angle to find left / right
        // 2. use which goal is the bigger one figure out which quadrant we're in
    // check that lidarData makes sense for that quadrant
        // the checks:
        // 1. add them up and see if they fit within a range (cause they should add to a fairly consistent number)
        // 2. check if the correct one is the greater one (based on quadrant)
            // -> if all goods (or some is ok) - use lidar data to calulate position
            // -> otherwise use the cameras

    /* Calculate ball position */
    // just use cam data and robots position
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
