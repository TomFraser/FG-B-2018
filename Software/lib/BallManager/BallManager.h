#ifndef BallManager_h
#define BallManager_h

#include <Arduino.h>
#include <ECUDriver.h>
#include <Timer.h>
#include <Enum.h>

class BallManager {
public:
    BallManager();
    /* TODO More here */
    bool controlBall(double ballConfidence, int goalDist, int angleToGoal);
private:
    void kickBall();
    ECUDriver backspin = ECUDriver(BACKSPIN_PIN);
    Timer timeSinceKick = Timer(0);

    solenoidMode mode;
};

extern BallManager kicker;

#endif
