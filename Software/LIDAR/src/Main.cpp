#include <Arduino.h>
#include <t3spi.h>
#include <Common.h>
#include <LIDARWrapper.h>

T3SPI LIDAR;

void transfer(){
    /* Respond based on request */
    switch(SPI0_POPR){
        case 0:
            SPI0_PUSHR_SLAVE = lidar.lidarVal[0]; break;
        case 1:
            SPI0_PUSHR_SLAVE = lidar.lidarVal[1]; break;
        case 2:
            SPI0_PUSHR_SLAVE = lidar.lidarVal[2]; break;
        case 3:
            SPI0_PUSHR_SLAVE = lidar.lidarVal[3]; break;
        default:
            65535; break;
    }
    /* Ensure we only send once */
    SPI0_SR |= SPI_SR_RFDF;
}

void setup(){
    /* Pin Setups */
    pinMode(10, INPUT);
    pinMode(MISO, OUTPUT);

    /* SPI setup */
    LIDAR.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    LIDAR.setCTAR_SLAVE(16, SPI_MODE0);
    attachInterrupt(digitalPinToInterrupt(10), transfer, LOW);

    /* Begin Serials for LIDARs */
    lidar.init();

}

void loop(){
    lidar.read();
    Serial.print(lidar.lidarVal[0]); Serial.print(" "); Serial.print(lidar.lidarVal[1]); Serial.print(" "); Serial.print(lidar.lidarVal[2]); Serial.print(" "); Serial.println(lidar.lidarVal[3]);
}
