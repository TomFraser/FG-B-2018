#ifndef Structs_h
#define Structs_h

struct controlData {
    double direction;
    int speed;
    bool followingBall;
};

struct coordinate {
    int x;
    int y;
};

struct cameraData {
    int ballAngle;
    int ballDist;
    int yGoalAngle;
    int yGoalDist;
    int bGoalAngle;
    int bGoalDist;
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

#endif
