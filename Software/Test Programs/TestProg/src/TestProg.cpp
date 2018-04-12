#include <Common.h>
#include <Config.h>

void setup(){
    Serial.begin(9600);
    pinMode(1, INPUT_PULLUP);
}

void loop(){
    Serial.println(digitalRead(1));
}
