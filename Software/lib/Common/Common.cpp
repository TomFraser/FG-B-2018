#include <Common.h>

bool isFrontal(int angle){
    /* Is the given angle within a small rangle */
    if(angle <= 15 || angle >= 345){
        return true;
    }
    return false;
}

bool isFrontalLarge(int angle){
    /* Is the given angle within a large rangle */
    if(angle <= 60 || angle >= 300){
        return true;
    }
    return false;
}

double doubleMod(double value, double maxVal){
    /* Modulus for doubles */
    return fmod((value + maxVal), maxVal);
}

void blink(){
    int led;
    ulong initTime;
    /* Blink the pin 13 LED */
    if(millis() > initTime + 1000 && DEBUG){
        if(led == 0){
            digitalWrite(13, HIGH);
            led = 1;
            initTime = millis();
        }else{
            digitalWrite(13, LOW);
            led = 0;
            initTime = millis();
        }
    }
}

bool lightGateTriggered(){
    /* Check if the lightgate is triggered */
    if(analogRead(LIGHTGATE_PIN) >= LIGHTGATE_THRESHOLD){
        return true;
    }
    return false;
}

double fromFront(double angle){
    /* Calulate and angle from the front of the robot based on a 0-360 angle */
    angle = angle == 0 ? 1 : angle;
    return angle < 180.0 ? (angle) : (360.0 - angle);
}

double calculateBallConfidence(double strength, double angle){
    /* Calculate ball confidence */
    double confidence = strength * 1/fromFront(angle); // REVIEW
}
