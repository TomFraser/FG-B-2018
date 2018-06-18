#include <CoordCalc.h>

CoordCalc::CoordCalc(){
  // init
}

/* Public Functions */
void CoordCalc::updateData(absCameraData cam, lidarData lidar, mode playMode){

    /* Calculate robot position */
    #if !SUPERTEAM
        // caculate an estimate of our position with the camera
        coordinate camCoords;
        if(playMode == mode::attacker){
            camCoords = {65506, 65506};
        } else {
            // Serial.println(cam.defenceAngle);

            if(abs(cam.defenceAngle) < 360){
                camCoords = calculateCamCoords(cam);
            } else {
                camCoords = {65506, 65506};
            }
        }
    #else
        coordinate camCoords;
        camCoords = {65506, 65506};
    #endif

    // Serial.print(camCoords.x); Serial.print(" "); Serial.println(camCoords.y);

    // Serial.print(lidar.leftDist); Serial.print(" "); Serial.print(lidar.rightDist); Serial.print(" "); Serial.print(lidar.frontDist); Serial.print(" "); Serial.println(lidar.backDist);

    bool leftXverify;
    bool rightXverify;
    bool frontYverify;
    bool backYverify;

    int leftX;
    int rightX;
    int frontY;
    int backY;

    leftX = lidar.leftDist != 65506 ? TABLE_LEFT_X + lidar.leftDist : 65506;
    rightX = lidar.rightDist != 65506 ? TABLE_RIGHT_X - lidar.rightDist : 65506;

    frontY = lidar.frontDist != 65506 ? TABLE_FRONT_Y - lidar.frontDist : 65506;
    backY = lidar.backDist != 65506 ? TABLE_BACK_Y + lidar.backDist : 65506;

    // Serial.print(leftX); Serial.print(" "); Serial.print(rightX); Serial.print(" "); Serial.print(frontY); Serial.print(" "); Serial.println(backY);

    if(camCoords.x != 65506 && camCoords.y != 65506){
        leftXverify = leftX != 65506 && inBaseRange(leftX, camCoords.x, LIDAR_CAM_RANGE);
        rightXverify = rightX != 65506 && inBaseRange(rightX, camCoords.x, LIDAR_CAM_RANGE);

        frontYverify = frontY != 65506 && inBaseRange(frontY, camCoords.y, LIDAR_CAM_RANGE);
        backYverify = backY != 65506 && inBaseRange(backY, camCoords.y, LIDAR_CAM_RANGE);
    } else {
        leftXverify = leftX != 65506;
        rightXverify = rightX != 65506;
        frontYverify = frontY != 65506;
        backYverify = backY != 65506;
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
    if(cam.ballAngle != 65506 && cam.ballDist != 65506){
        cam.ballAngle = mod(-cam.ballAngle-90, 360) + 90;
        ball.x = robot.x + cam.ballDist*sin(angToRad*cam.ballAngle);
        ball.y = robot.y + cam.ballDist*cos(angToRad*cam.ballAngle);
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
    bool attackGoal = (cam.attackAngle != 65506 && cam.attackDist != 65506);
    bool defenseGoal = (cam.defenceAngle != 65506 && cam.defenceDist != 65506);

    // Serial.print(attackGoal); Serial.print(" "); Serial.println(defenseGoal);

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

    returnCoord.x = returnCoord.x != 65506 ? returnCoord.x * -1 : 65506;

    return returnCoord;

}
