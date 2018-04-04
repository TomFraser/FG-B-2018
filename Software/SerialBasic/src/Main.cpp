#include <Arduino.h>
void setup(){
    Serial.begin(9600);
    Serial1.begin(9600);
}

void loop(){
    Serial.println(Serial1.available());
}
