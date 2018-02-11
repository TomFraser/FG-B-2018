#include <Arduino.h>
#include <SPI.h>
#include <LIDARWrapper.h>

volatile byte pos;
volatile bool process;

void setup(){
    Serial.begin(9600);
    pinMode(MISO, OUTPUT);
    SPCR |= _BV(SPE);
    SPI.attachInterrupt();
}

void loop(){
    lidar.read();
}

ISR(SPI_STC_vect){
    int command = SPDR;
    int data = -1;
    switch(command){
        case 1:
            data = lidar.values[0];
        case 2:
            data = lidar.values[1];
        case 3:
            data = lidar.values[2];
        case 4:
            data = lidar.values[3];
    }
    SPDR = data;
    while (!(SPSR & (1<<SPIF))){
    };
    return SPDR;
}
