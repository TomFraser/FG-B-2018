#include <SPIWrapper.h>

SPIWrapper spi = SPIWrapper();

SPIWrapper::SPIWrapper(){
    /* Declarations */
}

void SPIWrapper::initSPI(){
    /* set SS pin */
    pinMode(LIDAR_SS, OUTPUT);
    digitalWrite(LIDAR_SS, HIGH);

    /* Init and setup SPI */
    SPI.setSCK(ALT_SCK);
    SPI.setDataMode(SPI_MODE0);
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV32);
    SPI.begin();
}

void SPIWrapper::getIRData(){
    /* Request data from LIDAR Teensy */
    for(int i = 0; i < IR_TRANSFER_NUM; i++){
        digitalWrite(LIDAR_SS, LOW);
        tempIRData[i] = SPI.transfer16(i);
        delay(1);
        digitalWrite(LIDAR_SS, HIGH);
    }

    /* These values are clockwise and public */
    /* NOTE: Check that these lidars are in the correct order */
    /* tempIRData = FRONT LEFT RIGHT BACK */
    lidars = {frontBroken ? 65506 : tempIRData[1], backBroken ? 65506 : tempIRData[3], leftBroken ? 65506 : tempIRData[0], rightBroken ? 65506 : tempIRData[2]};
}
