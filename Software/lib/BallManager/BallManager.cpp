#include <BallManager.h>

BallManager kicker = BallManager();

BallManager::BallManager(){
    pinMode(KICKER_PIN, OUTPUT);
    digitalWrite(KICKER_PIN, LOW);
    timeSinceKick.reset();
}

bool BallManager::controlBall(double maxSpeed, double ballAngle){
    if(fromFront(ballAngle) > 60){
        maxSpeed == 0;
        backspin.setSpeed(0);
    }else{
        backspin.setSpeed(1/(pow(fromFront(ballAngle), 0.1)) * maxSpeed);
    }
    // Serial.println(1/(pow(fromFront(ballAngle), 0.1)) * maxSpeed);
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
