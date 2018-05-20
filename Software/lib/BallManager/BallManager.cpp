#include <BallManager.h>

BallManager kicker = BallManager();

BallManager::BallManager(){
    pinMode(KICKER_PIN, OUTPUT);
    digitalWrite(KICKER_PIN, LOW);
    timeSinceKick.reset();
}

bool BallManager::controlBall(double ballDist, int goalDist, int angleToGoal){
    if(goalDist <= KICK_DIST && angleToGoal <= MIN_GOAL_ANGLE){
        backspin.setSpeed(1000);
        delay(5);
        kickBall();
    }else{
        /* Here, we need to find the min distance to the ball */
        backspin.setSpeed(ballDist);
    }
}

void BallManager::kickBall(){
    if(timeSinceKick.hasBeenMS(2000)){
        if(mode = solenoidMode::canKick){
            digitalWrite(KICKER_PIN, HIGH);
            delay(5);
            digitalWrite(KICKER_PIN, LOW);
            timeSinceKick.reset();
        }
    }
}
