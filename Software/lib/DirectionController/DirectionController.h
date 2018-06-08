#ifndef DirectionController_h
#define DirectionController_h

#include <Arduino.h>
#include <Common.h>
#include <Structs.h>
#include <LightTracker.h>
#include <CoordCalc.h>
#include <PID.h>
#include <Orbit.h>
#include <CoordMover.h>

class DirectionController{

public:
    /* Functions */
    void attackingYellow(bool attackYellow_);
    void updateData(cameraData cam_, lidarData lidar_, lightData light_, xbeeData xbee_, double compass_, mode playMode_);
    moveControl calculate();
    xbeeData getXbeeData();

    /* Variables */

private:
    /* Functions */
    double relToAbs(double relativeDirection);
    double absToRel(double absoluteDirection);
    uint16_t relToAbsLidar(uint16_t value, double zeroHeading);
    moveControl calculateReturn(moveControl tempControl);
    moveControl calculateAttack();
    moveControl calculateGoalie();
    lidarData adjustLidar(lidarData lidar);
    moveControl calculateSpiral(double target);


    /* Objects */
    LightTracker lightTracker = LightTracker();
    CoordCalc coordCalc = CoordCalc();
    CoordMover coordMover = CoordMover();
    // PIDs
    PID rotationPID = PID(-5, -0.1, -0.2, 0.00);
    PID goalTrackingPID = PID(-3, -0.1, -0.2, 0.00);
    // Goalie pids
    PID goalieAnglePID = PID(-4, 0, -0.5, 0.00);
    PID goalieSonarPID = PID(2.50, 0.00, 0.2, 0.00);
    PID goalieVerPID = PID(2.00, 0.00, 0.2, 0.00);

    /* Variables */

    /* Spiral */
    bool isSpiral = false;
    long initialSpiralTime;
    double ballLocation = 65506;
    bool goingDirection;
    bool goingOpposite;
    double spiralAdd;
    double spiralDirection;

    // input data
    mode playMode;
    bool attackYellow;
    absCameraData cam;
    lidarData lidar;
    lightData light;
    xbeeData xbee;
    double compass;
    double moveAngle;
    double gyration;

    double rPID, gPID;

    // coordinate data
    coordinate myBallCoord;
    coordinate myRobotCoord;

};

extern DirectionController dc;

#endif
