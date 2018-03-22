#include <Arduino.h>
#include <SPI.h>
// #include <LIDARWrapper.h>
#include <Common.h>

void setup(){
    Serial.begin(9600);
    pinMode(MISO, OUTPUT);
    SPI.setDataMode(SPI_MODE0);
    SPI.setBitOrder(LSBFIRST);
    SPCR |= _BV(SPE);
    SPI.attachInterrupt();
}

void loop(){
    // lidar.read();
}

ISR(SPI_STC_vect){
    int command = SPDR;
    int data = -1;
    switch(command){
        case 1:
            data = 1;
        case 2:
            data = 2;
        case 3:
            data = 3;
        case 4:
            data = 4;
    }
    SPDR = data;
    while (!(SPSR & (1<<SPIF))){
    }
    return SPDR;
}
