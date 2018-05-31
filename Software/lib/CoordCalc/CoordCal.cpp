#include <CoordCalc.h>

CoordCalc::CoordCalc(){
  // init
}

/* Public Functions */
void CoordCalc::updateData(absCameraData cam, lidarData lidar){

    /* Calculate robot position */
    // caculate an estimate of our position with the camera
    // Serial.println(cam.attackDist);
    coordinate camCoords = calculateCamCoords(cam);

    // Serial.print(camCoords.x); Serial.print(" "); Serial.println(camCoords.y);

    bool leftXverify;
    bool rightXverify;
    bool frontYverify;
    bool backYverify;

    int leftX;
    int rightX;
    int frontY;
    int backY;

    if(lidar.leftDist != 65506){
        // calculate coordinates based on lidar data
        leftX = TABLE_LEFT_X - lidar.leftDist;
        rightX = TABLE_RIGHT_X + lidar.rightDist;

        frontY = TABLE_FRONT_Y - lidar.frontDist;
        backY = TABLE_BACK_Y + lidar.backDist;

        // Serial.print(leftX); Serial.print(" "); Serial.println(rightX);

        // verify lidar with camera (if we cant see the goal with cam - just assume lidar is correct)
        if(camCoords.x != 65506 && camCoords.y != 65506){
            leftXverify = inBaseRange(leftX, camCoords.x, LIDAR_CAM_RANGE);
            rightXverify = inBaseRange(rightX, camCoords.x, LIDAR_CAM_RANGE);

            frontYverify = inBaseRange(frontY, camCoords.y, LIDAR_CAM_RANGE);
            backYverify = inBaseRange(backY, camCoords.y, LIDAR_CAM_RANGE);
        } else {
            leftXverify = true;
            rightXverify = true;
            frontYverify = true;
            backYverify = true;
        }
    } else {
        leftXverify = false;
        rightXverify = false;
        frontYverify = false;
        backYverify = false;
    }

    // calulate final x
    if(leftXverify && rightXverify){
        // take the smaller lidar distance (cause its likely to be more accurate)
        if (lidar.leftDist < lidar.rightDist){
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
        if (lidar.frontDist < lidar.backDist){
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
    if(cam.ballAngle != 65506){
        ball.x = robot.x + cam.ballDist*sin(angToRad*cam.ballDist);
        ball.y = robot.y + cam.ballDist*cos(angToRad*cam.ballDist);
    } else {
        ball.x = 65506;
        ball.y = 65506;
    }
}


/* Private Functions */
coordinate CoordCalc::calculateCamCoords(absCameraData cam){

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
