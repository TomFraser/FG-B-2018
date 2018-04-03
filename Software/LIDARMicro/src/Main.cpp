#include <Arduino.h>
// #include <SPI.h>
#include <LIDARWrapper.h>
#include <Common.h>

void setup(){
    pinMode(MISO, OUTPUT);
    pinMode(13, OUTPUT);
    /* Set up SPI settings and enable Interrupts */
    SPCR=(1<<SPE)|(0<<CPOL)|(0<<CPHA)|(0<<DORD)|(0<<MSTR)|(1<<SPIE);
}

void loop(){
    lidar.read();

    uint8_t data = SPDR;
    switch(data){
        case 1:
            SPDR = lidar.values[0] & 0x00ff;
        case 2:
            SPDR = (lidar.values[0] >> 8);
        case 3:
            SPDR = lidar.values[1] & 0x00ff;
        case 4:
            SPDR = (lidar.values[1] >> 8);
        case 5:
            SPDR = lidar.values[2] & 0x00ff;
        case 6:
            SPDR = (lidar.values[2] >> 8);
        case 7:
            SPDR = lidar.values[3] & 0x00ff;
        case 8:
            SPDR = (lidar.values[3] >> 8);
    }
    while (!(SPSR & (1<<SPIF)));
}
