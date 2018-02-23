#include <SPIWrapper.h>

SPIWrapper spi = SPIWrapper();

SPIWrapper::SPIWrapper(){
    /* Declarations */
}

void SPIWrapper::initSPI(){
    /* Init and setup SPI */
    pinMode(CAM_SS, OUTPUT);
    SPI.begin();
    digitalWrite(CAM_SS, HIGH);
    SPI.setSCK(ALT_SCK);
    SPI.setClockDivider(SPI_CLOCK_DIV8);
}

bool SPIWrapper::getIRData(){
    /* Reset data in tempIRData array to -1 */
    memset(tempIRData, -1, sizeof(tempIRData));
    /* Request data from IRMicro */
    for(int i = 0; i < IR_TRANSFER_NUM; i++){
        digitalWrite(IR_SS, LOW);
        tempIRData[i] = SPI.transfer16(i);
        digitalWrite(IR_SS, HIGH);
    }
    /* Set the data collected to variable that will be used publically */
    /* These values are clockwise */
    frontIR = tempIRData[0];
    rightIR = tempIRData[1];
    backIR = tempIRData[2];
    leftIR = tempIRData[3];
    /* Change to return false if all data is the same (-1) */
    if(sumArr(tempIRData) == -4){
        return false;
    }
    return true;
}
