#ifndef DirectionController_h
#define DirectionController_h

#include <Arduino.h>
#include <Common.h>
#include <Structs.h>
#include <LightTracker.h>
#include <CoordCalc.h>
#include <PID.h>
#include <Orbit.h>

class DirectionController{

public:
    /* Functions */
    void attackingYellow(bool attackYellow_);
    void updateData(cameraData cam_, lidarData lidar_, lightData light_, xbeeData xbee_, double compass_);
    moveControl calculate(mode robotMode);
    xbeeData getXbeeData();

    /* Variables */

private:
    /* Functions */
    double relToAbs(double relativeDirection);
    double absToRel(double absoluteDirection);
    uint16_t relToAbsLidar(uint16_t value);
    moveControl calculateReturn(moveControl tempControl);
    moveControl calculateAttack();
    moveControl calculateGoalie();
    lidarData adjustLidar(lidarData lidar);


    /* Objects */
    LightTracker lightTracker = LightTracker();
    CoordCalc coordCalc = CoordCalc();
    PID rotationPID = PID(-5, -0.1, -0.2, 0.00);
    PID goalTrackingPID = PID(-3, -0.1, -0.2, 0.00);
    // Goalie pids
    PID goalieAnglePID = PID(-5, -0.1, -0.2, 0.00);
    PID goalieSonarPID = PID(2.50, 0.00, 0.2, 0.00);
    //NEEDS TO BE TUNED WHEN LIDARS ARE RAISED ABOVE GOAL
    // also new target needs to be set
    PID goalieVerPID = PID(1.00, 0.00, 0.00, 0.00);

    /* Variables */

    // input data
    bool attackYellow;
    absCameraData cam;
    lidarData lidar;
    lightData light;
    xbeeData xbee;
    double compass;
    double moveAngle;
    double gyration;

    double notnotrotationvariablevariable, notnotrotationvariablevariable2;

    // coordinate data
    coordinate myBallCoord;
    coordinate myRobotCoord;

};

extern DirectionController dc;

#endif
