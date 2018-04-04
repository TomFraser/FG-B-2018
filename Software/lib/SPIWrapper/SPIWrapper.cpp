#include <SPIWrapper.h>

SPIWrapper spi = SPIWrapper();

SPIWrapper::SPIWrapper(){
    /* Declarations */
}

void SPIWrapper::initSPI(){
    /* Init and setup SPI */
    SPI.setSCK(ALT_SCK);
    SPI.setDataMode(SPI_MODE0);
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV64);
    SPI.begin();
}

void SPIWrapper::getIRData(){
    /* Reset data in tempIRData array to -1 */
    memset(tempIRData, -1, sizeof(tempIRData));
    /* Request data from IRMicro */
    for(int i = 0; i < IR_TRANSFER_NUM; i++){
        tempIRData[i] = SPI.transfer(i);
    }
    /* Set the data collected to variable that will be used publically */
    /* These values are clockwise */
    for(int i = 0; i < IR_TRANSFER_NUM; i++){
        Serial.println(tempIRData[i]);
    }
    // frontIR = (tempIRData[2] << 8) | tempIRData[1];
    // Serial.println(frontIR);
    // rightIR = (tempIRData[3] << 8) | tempIRData[2];
    // backIR = (tempIRData[5] << 8) | tempIRData[4];
    // leftIR = (tempIRData[7] << 8) | tempIRData[6];
}
