#include <BallManager.h>

BallManager kicker = BallManager();

BallManager::BallManager(){
    pinMode(KICKER_PIN, OUTPUT);
    digitalWrite(KICKER_PIN, LOW);
    timeSinceKick.reset();
}

bool BallManager::controlBall(double maxSpeed, double ballAngle){
    if(fromFront(ballAngle) > 75){
        maxSpeed == 0;
        backspin.setSpeed(0);
    }else{
        backspin.setSpeed(1/(pow(fromFront(ballAngle), 0.05)) * maxSpeed);
    }
    // Serial.println(1/(pow(fromFront(ballAngle), 0.1)) * maxSpeed);
}

bool BallManager::controlBall(double speed){
    backspin.setSpeed(speed);
}

bool BallManager::hasBall(){
    return !digitalRead(A12);
}

void BallManager::kickBall(){
    if(timeSinceKick.hasBeenMS(2000)){
        if(mode == solenoidMode::canKick){
            // backspin.setSpeed(0);
            // delay(5);
            digitalWrite(KICKER_PIN, HIGH);
            delay(5);
            digitalWrite(KICKER_PIN, LOW);
            timeSinceKick.reset();
        }
    }
}
