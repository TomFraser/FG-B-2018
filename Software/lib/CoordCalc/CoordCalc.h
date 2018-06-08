#ifndef CoordCalc_h
#define CoordCalc_h

#include <Arduino.h>
#include <Common.h>
#include <Structs.h>

class CoordCalc{

public:
    CoordCalc();

    /* Functions */
    void updateData(absCameraData cam, lidarData lidar, mode playMode);

    /* Variables */
    coordinate ball;
    coordinate robot;

private:

    /* Functions */
    coordinate calculateCamCoords(absCameraData cam);

    /* Variables */
    double compass;
};
#endif
