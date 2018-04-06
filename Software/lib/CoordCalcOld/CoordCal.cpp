// UNLESS YOU ARE AL DO NOT TOUCH OR I WILL END YOU SLOWLY AND
// PAINFULLY BY MAKING YOU DO THE MERGE

// TODO: need to write a thing to deal with it spazzing out at the sides

#include <CoordCalc.h>

CoordCalc::CoordCalc(){
  // init
}

int CoordCalc::calcDistance(int goalArea, int goalAngle, bool attack){
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

bool CoordCalc::update(int areaA, int angleA, int areaD, int angleD, double compassAngle){
  // returns the success of the coord calc
  // if true then can use the get coords functions
  // if false then have to do something else


  //-30 is the 'no goal' angle
  bool attackGoal = (angleA != 65506);
  bool defenseGoal = (angleD != 65506);

  // attack calulations
  if(attackGoal){

    angleA = doubleMod(angleA - compassAngle, 360); // CHECK THIS

    int distance = calcDistance(areaA, angleA, true);

    // Serial.println(distance);

    if(distance < 150 && distance > 0)
    {
      int xGoal = distance*sin(angToRad*angleA);
      int yGoal = distance*cos(angToRad*angleA);

      xAttack = ATTACK_GOAL_X-xGoal;
      yAttack = ATTACK_GOAL_Y-yGoal;

      // Serial.println(xAttack);
      // Serial.println(yAttack);
      // Serial.println();
    }
    else{
      attackGoal = false;
    }

  }

  // defense calulations
  if(defenseGoal){
    angleD = doubleMod(angleD - compassAngle, 360); // CHECK THIS

    int distance = calcDistance(areaD, angleD, false);

    // Serial.println(distance);

    if(distance < 150 && distance > 0)
    {
      int xGoal = distance*sin(angToRad*angleD);
      int yGoal = distance*cos(angToRad*angleD);

      xDefense = DEFENSE_GOAL_X-xGoal;
      yDefense = DEFENSE_GOAL_Y-yGoal;

      // Serial.println(xDefense);
      // Serial.println(yDefense);
      // Serial.println();
    }
    else{
      defenseGoal = false;
    }
  }

  if(attackGoal && defenseGoal){
    // we can see both goals
    // so yeah, idk what were gonna do here maybe average
    // what happens when one memes tho? we cant really tell which
    // one is correct and the other is a meme

    // take the smaller goal (smaller distance = closer)
    if(areaA < areaD){
      xCoord = xAttack;
      yCoord = yAttack;
    }
    else{
      xCoord = xDefense;
      yCoord = yDefense;
    }

  }
  else if(attackGoal){
    // only attack goal can be seen
    xCoord = xAttack;
    yCoord = yAttack;
  }
  else if(defenseGoal){
    // only defenseGoal can be seen
    xCoord = xDefense;
    yCoord = yDefense;
  }
  else{
    // no goals
    return false;
  }

  // Serial.println(xCoord);
  // Serial.println(yCoord);
  // Serial.println();
  //
  // make sure our coords are within the field - ceebs doing this, i dont think its good
  // return (FRONT_LEFT_X < xCoord && xCoord < FRONT_RIGHT_X) && (FRONT_LEFT_Y < yCoord && yCoord < BACK_LEFT_Y);
  return true;
}

int CoordCalc::getX(){
  return xCoord;
}

int CoordCalc::getY(){
  return yCoord;
}
