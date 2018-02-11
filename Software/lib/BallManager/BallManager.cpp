#include <BallManager.h>

BallManager::BallManager(){
    timeSinceKick.reset();
}

bool BallManager::controlBall(double ballConfidence){
    if(ballConfidence >= MIN_BALL_CONFIDENCE && ballConfidence <= BALL_CONFIDENCE){
        mode = solenoidMode::lowSpeed;
    }else if(ballConfidence >= BALL_CONFIDENCE){
        mode = solenoidMode::highSpeed;
    }else if(ballConfidence < MIN_BALL_CONFIDENCE){
        mode = solenoidMode::noSpeed;
    }
    if(lightGateTriggered()){
        mode = solenoidMode::hasBall;
        if(timeSinceKick.hasBeenMS(500)){
            mode = solenoidMode::canKick;
        }
    }
    return true; //Remove
}

void BallManager::kickBall(){
    if(mode = solenoidMode::canKick){
        digitalWrite(KICKER_PIN, HIGH);
        delay(20);
        digitalWrite(KICKER_PIN, LOW);
        timeSinceKick.reset();
    }
}
