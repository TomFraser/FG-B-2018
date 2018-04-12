#include <BallManager.h>

BallManager kicker = BallManager();

BallManager::BallManager(){
    pinMode(KICKER_PIN, OUTPUT);
    digitalWrite(KICKER_PIN, LOW);
    timeSinceKick.reset();
}

bool BallManager::controlBall(double ballConfidence){
    // if(ballConfidence >= MIN_BALL_CONFIDENCE && ballConfidence < BALL_CONFIDENCE){
    //     mode = solenoidMode::lowSpeed;
    // }else if(ballConfidence >= BALL_CONFIDENCE){
    //     mode = solenoidMode::highSpeed;
    // }else if(ballConfidence < MIN_BALL_CONFIDENCE){
    //     mode = solenoidMode::noSpeed;
    // }
    // backspin.setSpeed(mode);
    // mode = solenoidMode::canKick;
    backspin.setSpeed(ballConfidence);
}

void BallManager::kickBall(){
    if(timeSinceKick.hasBeenMS(2000)){
        if(mode = solenoidMode::canKick){
            digitalWrite(KICKER_PIN, HIGH);
            delay(25);
            digitalWrite(KICKER_PIN, LOW);
            timeSinceKick.reset();
        }
    }
}
