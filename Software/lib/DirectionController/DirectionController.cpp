#include <DirectionController.h>

DirectionController::DirectionController(){
  // setup PID
  // pid.SetMode(AUTOMATIC);
  // pid.SetOutputLimits(0, 100); // speed is 0-100
  // pid.SetSampleTime(25); //CHECK IF I NEED TO SET THIS TO SMALLER THAN 200mS
}

double DirectionController::getDirection(){
  return direction;
}

int DirectionController::getSpeed(){
  return speed;
}

bool DirectionController::getFollowingBall(){
  return followingBall;
}

int DirectionController::getX(){
  return currX;
}

int DirectionController::getY(){
  return currY;
}

double DirectionController::relToAbs(double relativeDirection){
  return relativeDirection != 65506 ? doubleMod(relativeDirection - compassAngle, 360.0) : 65506;
}

double DirectionController::absToRel(double absoulteDirection){
  return absoulteDirection != 65506 ? doubleMod(absoulteDirection + compassAngle, 360.0) : 65506;
}

void DirectionController::updateGameData(double ballAngle_, double rawBallAngle_, int ballStrength_, double lightAngle_, int numSensors_, double compassAngle_, bool isGoalie_){
  if(ballAngle != 65506){
    prevBallAngle = ballAngle; // prevBallAngle is last known ball
  }

  compassAngle = compassAngle_;
  ballStrength = ballStrength_;
  numSensors = numSensors_;
  isGoalie = isGoalie_;

  ballAngle = relToAbs(ballAngle_);
  rawBallAngle = relToAbs(rawBallAngle_);
  lightAngle = relToAbs(lightAngle_);

  if(lightAngle != 65506){
    // if(lightAngle != targetDir){
    //   resetSpiral();
    // }
    targetDir = lightAngle; // the direction we will target spiral towards
  }


  followingBall = false;
}

void DirectionController::updateGoalData(int areaA_, int angleA_, int areaD_, int angleD_){
  areaA = areaA_;
  angleA = angleA_;
  areaD = areaD_;
  angleD = angleD_;

  updateCoordinates();
  updateBallCoordinates();
}

void DirectionController::updateOtherData(int otherBallX_, int otherBallY_, int otherRobotX_, int otherRobotY_, bool otherCanSeeBall_, bool otherKnowsOwnCoords_){
  otherBallX = otherBallX_;
  otherBallY = otherBallY_;

  otherRobotX = otherRobotX_;
  otherRobotY = otherRobotY_;

  otherCanSeeBall = otherCanSeeBall_;
  otherKnowsOwnCoords = otherKnowsOwnCoords_;
}

// ------------------------ Ball stuff -----------------------------------

int DirectionController::calcBallDist(){
  // gotta figure out an algorithm for this
  if(ballStrength > 15 && ballStrength < 122){
    return -sqrt(9550-pow(ballStrength-15, 2))+98;
  }
  else{
    return -1;
  }

}

void DirectionController::updateBallCoordinates(){ //returns if can calulate ball coords
  prevBallX = getAllBallX();
  int ballDist = calcBallDist();
  if(rawBallAngle != 65506 && currX != 65506 && currY != 65506 && ballDist > 0){
    ballX = currX + ballDist*sin(angToRad*rawBallAngle);
    ballY = currY + ballDist*cos(angToRad*rawBallAngle);
  }
  else{
    ballX = 65506;
    ballY = 65506;
  }
}

int DirectionController::getBallX(){
  return ballX;
}

int DirectionController::getBallY(){
  return ballY;
}

double DirectionController::getBallAngle(){
  if(rawBallAngle != 65506){
    return rawBallAngle;
  }
  else{
    if(otherCanSeeBall){
      return atan2(otherBallX-currX, otherBallY-currY)*radToAng; //if cant see the ball, use the other robots ball xy
    }
    else{
      return 65506; // no one can see the ball -> dunno where it is
    }
  }
}

// -----------------------------------------------------------------------------------

void DirectionController::updateCoordinates(){
  if(coordCalc.update(areaA, angleA, areaD, angleD, compassAngle)){ // returns false if cant see any goal
    currX = coordCalc.getX();
    currY = coordCalc.getY();
  }
  else{
    currX = 65506;
    currY = 65506;
  }
}

void DirectionController::goToCoords(int targetX, int targetY){
  double coordDirection;
  double coordSpeed;
  // if coordinates = 65506, cant see goal and cant figure out where we are -> stop
  if(currX == 65506 || currY == 65506){
    coordDirection = 65506;
    coordSpeed = 0;
  }
  else{
    // all good -> go for it
    // we know where we are, gotta figure out how to where we wanna be
    int deltaX = targetX - currX;
    int deltaY = targetY - currY;
    int distance = (int)sqrt((deltaX*deltaX) + (deltaY*deltaY));
    distance = distance < (isGoalie ? DISTANCE_CUTOFF_GOALIE : DISTANCE_CUTOFF_ATTACK) ? 0 : distance;

    coordDirection = atan2(deltaX, deltaY) * radToAng; // coords -180 to 180 on North
    // convert to 0-360
    coordDirection = coordDirection < 0 ? coordDirection + 360 : coordDirection;


    // #if ENABLE_PID
      // pidInput = distance;
      // Serial.print(pidInput); Serial.print(" ");
      // pid.Compute();
      // Serial.println(pidOutput);
      // coordSpeed = pidOutput;
    // #else
      coordSpeed = (int) (distance * (distance < DISTANCE_CUTOFF ? CUTOFF_SPEED_SCALE : COORD_SPEED_SCALE));
    // #endif
  }

  // make sure our great overlord the light tracker is happy
  lightTracker.update(lightAngle, coordDirection, coordSpeed, rawBallAngle, numSensors);
  direction = absToRel(lightTracker.getDirection());
  speed = lightTracker.getSpeed();

}

int DirectionController::getAllBallX(){
  #if XBEE_ENABLE
    if(ballX != 65506){
      return ballX;
    }
    else if(otherCanSeeBall){
      return otherBallX;
    }
    else{
      return 65506;
    }
  #else
    return ballX;
  #endif

}

int DirectionController::getAllBallY(){
  #if XBEE_ENABLE
    if(ballY != 65506){
      return ballY;
    }
    else if(otherCanSeeBall){
      return otherBallY;
    }
    else{
      return 65506;
    }
  #else
    return ballY;
  #endif
}


void DirectionController::calculateAttack(){

  // if(currX != 65506 && currY != 65506 && currY < ATTACKER_MIN_Y && lightAngle == 65506){
  //   if(smallestAngleBetween(lightAngle, 270) < 45){
  //     lightAngle = 315;
  //   }
  //   else if(smallestAngleBetween(lightAngle, 90) < 45){
  //     lightAngle = 45;
  //   }
  //   else{
  //     lightAngle = 0;
  //   }
  // }

  // if got ball -> plug into light
  if(ballAngle != 65506){
    resetSpiral(rawBallAngle);
    lightTracker.update(lightAngle, ballAngle, SPEED_VAL, rawBallAngle, numSensors);
    direction = absToRel(lightTracker.getDirection());
    speed = lightTracker.getSpeed();
    followingBall = lightTracker.getNormalGameplay();
  }
  else{
    // cant see ball -> go to ball or predefined pos
    int allBallX = getAllBallX();
    int allBallY = getAllBallY();

    if(allBallX != 65506 && allBallY != 65506){
      goToCoords(allBallX, allBallY);
    }
    #if ENABLE_SPIRAL
    else if(currX == 65506 || currY == 65506 || (abs(currX - TARGET_X) < SPIRAL_COORD_DIST) && abs(currY - TARGET_Y) < SPIRAL_COORD_DIST){
      doSpiral();
    }
    #endif
    else{
      if(currY < 0){
        resetSpiral(0);
      }
      else{
        resetSpiral(180);
      }
      goToCoords(TARGET_X, TARGET_Y);
    }
  }
}

void DirectionController::resetSpiral(int target){
  isSpiraling = false;
  targetDir = target;
}

void DirectionController::doSpiral(){
  // spiral
  if(isSpiraling){
    double add;
    bool goingDirection;
    bool goingOpposite;
    #if ENABLE_TARGET_SPIRAL
      // Serial.println(targetDir);
      if(targetDir != -1){
        goingDirection = smallestAngleBetween(targetDir, spiralDirection) < 1;
        goingOpposite = abs(smallestAngleBetween(targetDir, spiralDirection)-180) < 45;
      }
      else{
        goingDirection = false;
        goingOpposite = false;
      }
    #else
      goingDirection = false;
      goingOpposite = false;
    #endif

    if(goingDirection){
      add = 1000.0/(millis() - startSpiralTime + SPIRAL_CONST) * SPIRAL_DIRECION_RATE;
    }
    else if(goingOpposite){
      add = 1000.0/(millis() - startSpiralTime + SPIRAL_CONST) * (1/SPIRAL_DIRECION_RATE);
    }
    else{
      add = 1000.0/(millis() - startSpiralTime + SPIRAL_CONST) * SPIRAL_RATE;
    }

    spiralDirection = fmod(spiralDirection + add, 360);

    #if ENABLE_TARGET_SPIRAL
    bool canReset = true;
    if(targetDir != -1){
      canReset = smallestAngleBetween(targetDir + 90, spiralDirection) < 1;
    }
    if(add < SPIRAL_RESET && !goingDirection && canReset){
    #else
    if(add < SPIRAL_RESET && !goingDirection){
    #endif
      resetSpiral();
    }
  }
  else{
    spiralDirection = prevBallAngle;
    startSpiralTime = millis();
    isSpiraling = true;
  }

  lightTracker.update(lightAngle, spiralDirection, SPIRAL_SPEED, rawBallAngle, numSensors);
  direction = absToRel(lightTracker.getDirection());
  speed = lightTracker.getSpeed();
  followingBall = false;
}

void DirectionController::calculateGoalie(){
  // basically the strat is just go to the balls x whilst remaining at a constant y
  int targetX;
  int targetY;
  int allBallX = getAllBallX();
  int allBallY = getAllBallY();

  // Serial.println(allBallX);
  // Serial.println(allBallY);

  if(allBallX != 65506){
    // if(prevBallX != 65506){
    //   targetX = allBallX + (allBallX - prevBallX)*25;
    // }
    // else{
    //   targetX = allBallX;
    // }

    targetX = allBallX;

    #if ENABLE_GOALIE_SURGE
      if(abs(allBallX-currX) < SURGE_X && (allBallY-currY < SURGE_Y && allBallY-currY > 0 && allBallY < SURGE_MAX_Y)){
        targetY = allBallY;
      }
      else{
        targetY = GOALIE_Y;
      }
    #else
      targetY = GOALIE_Y;
    #endif
  }
  else{
    targetX = 0;
    targetY = GOALIE_Y;
  }

  if(targetX > GOALIE_X_RANGE) targetX = GOALIE_X_RANGE;
  if(targetX < -GOALIE_X_RANGE) targetX = -GOALIE_X_RANGE;

  // Serial.println(targetX);
  // Serial.println(targetY);
  // Serial.println();
  //

  goToCoords(targetX, targetY);
}
