#ifndef Common_h
#define Common_h

#include <Arduino.h>
#include <Config.h>


ulong initTime;
int led;

bool isFrontal(int angle){
    // Is the given angle within a small rangle
    if(angle <= 15 || angle >= 345){
        return true;
    }
    return false;
}

bool isFrontalLarge(int angle){
    // Is the given angle within a large rangle
    if(angle <= 60 || angle >= 300){
        return true;
    }
    return false;
}

double doubleMod(double value, double maxVal){
    // Modulus for doubles
    return fmod((value + maxVal), maxVal);
}

void blink(){
    // Blink the pin 13 LED
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
    if(analogRead(LIGHTGATE_PIN) >= LIGHTGATE_THRESHOLD){
        return true;
    }
    return false;
}

enum solenoidMode {
    noSpeed,
    lowSpeed,
    highSpeed,
    hasBall,
    canKick,
};

#endif
