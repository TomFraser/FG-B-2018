#ifndef Structs_h
#define Structs_h

struct moveControl {
    double direction;
    int speed;
    bool doBoost;
};

struct coordinate {
    int x;
    int y;
};

struct cameraData {
    int ballAngle;
    int ballStrength;
    int yGoalAngle;
    int yGoalStrength;
    int bGoalAngle;
    int bGoalStrength;
    bool attackingYellow;
};

struct lidarData {
    uint16_t frontDist;
    uint16_t backDist;
    uint16_t leftDist;
    uint16_t rightDist;
};

struct lightData {
    double angle;
    int numSensors;
};

struct xbeeData {
    coordinate ballCoords;
    coordinate robotCoords;
    bool seesBall;
    bool knowsPosition;
};

#endif
