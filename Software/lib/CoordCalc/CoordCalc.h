#ifndef CoordCalc_h
#define CoordCalc_h

#include <Arduino.h>
#include <Common.h>

class CoordCalc{

public:
    CoordCalc();

    /* Functions */
    void updateData(int areaA, int angleA, int areaD, int angleD, double compassAngle);

    /* Variables */
    coordinate ball;
    coordinate robot;

private:


};
#endif
