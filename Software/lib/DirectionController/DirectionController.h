#ifndef DirectionController_h
#define DirectionController_h

#include <Arduino.h>
#include <Common.h>
#include <Structs.h>
#include <LightTracker.h>
#include <CoordCalc.h>

class DirectionController{

public:
    /* Functions */
    void attackingYellow(bool attackYellow_);
    void updateData(cameraData cam_, lidarData lidar_, lightData light_, xbeeData xbee_, double compass_);
    moveControl calculate(bool attack);
    xbeeData getXbeeData();

    /* Variables */

private:
    /* Functions */
    double relToAbs(double relativeDirection);
    double absToRel(double absoluteDirection);
    double getOrbit(double direction);
    moveControl calculateAttack();
    moveControl calculateGoalie();

    /* Objects */
    LightTracker lightTracker = LightTracker();
    CoordCalc coordCalc = CoordCalc();

    /* Variables */

    // input data
    bool attackYellow;
    cameraData cam;
    lidarData lidar;
    lightData light;
    xbeeData xbee;
    double compass;
    double moveAngle;

    // coordinate data
    coordinate myBallCoord;
    coordinate myRobotCoord;

};

extern DirectionController dc;

#endif
