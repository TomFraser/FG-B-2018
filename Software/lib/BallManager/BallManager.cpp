#include <BallManager.h>

BallManager kicker = BallManager();

BallManager::BallManager(){
    pinMode(KICKER_PIN, OUTPUT);
    digitalWrite(KICKER_PIN, LOW);
    timeSinceKick.reset();
    kickerDischarge.reset();
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
    Serial.print("Discharge: "); Serial.println(kickerDischarge.getTime());
    Serial.print("Time Since: "); Serial.println(timeSinceKick.getTime());

    if(kickerDischarge.hasBeenMS(65)){
        if(timeSinceKick.hasBeenMS(1500)){
            digitalWrite(KICKER_PIN, HIGH);
            kickerDischarge.reset();
            timeSinceKick.reset();
        }else{
            digitalWrite(KICKER_PIN, LOW);
        }
    }
}
