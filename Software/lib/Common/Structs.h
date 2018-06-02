#ifndef Structs_h
#define Structs_h

struct moveControl {
    double direction;
    int speed;
    bool doBoost;
    double rotation;
};

struct coordinate {
    int x;
    int y;
};

struct moveTarget {
    coordinate target;
    double heading;
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

struct absCameraData {
    int ballAngle;
    int ballDist;
    int attackAngle;
    int attackDist;
    int defenceAngle;
    int defenceDist;
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
