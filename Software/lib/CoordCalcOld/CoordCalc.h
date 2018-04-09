// UNLESS YOU ARE AL DO NOT TOUCH OR I WILL END YOU SLOWLY AND
// PAINFULLY BY MAKING YOU DO THE MERGE

#ifndef CoordCalc_h
#define CoordCalc_h

#include <Arduino.h>
#include <Common.h>

class CoordCalc{

public:
    CoordCalc();


    bool update(int areaA, int angleA, int areaD, int angleD, double compassAngle);

    int calcDistance(int goalArea, int goalAngle, bool attack);

    int getX();
    int getY();

private:

  //value to store our current x
  int xCoord;

  //value to store our current y
  int yCoord;

  //value to store current attack x
  int xAttack;

  //value to store current attack y
  int yAttack;

  //value to store current defense x
  int xDefense;

  //value to store current defense y
  int yDefense;
};
#endif
