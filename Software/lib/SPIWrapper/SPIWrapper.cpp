#include <SPIWrapper.h>

SPIWrapper spi = SPIWrapper();

SPIWrapper::SPIWrapper(){
    /* Declarations */
}

void SPIWrapper::initSPI(){
    /* Init and setup SPI */
    SPI.setClockDivider(SPI_CLOCK_DIV32);
    SPI.setSCK(ALT_SCK);
    SPI.setDataMode(SPI_MODE0);
    SPI.setBitOrder(LSBFIRST);
    pinMode(10, OUTPUT);
    SPI.begin();
    digitalWrite(10, HIGH);
}

bool SPIWrapper::getIRData(){
    /* Reset data in tempIRData array to -1 */
    // memset(tempIRData, -1, sizeof(tempIRData));
    /* Request data from IRMicro */
    // for(int i = 0; i < IR_TRANSFER_NUM; i++){
        // tempIRData[i] = SPI.transfer16(i);
        digitalWrite(10, LOW);
        Serial.println(SPI.transfer(0));
        delay(1);
        digitalWrite(10, HIGH);
        delay(100);
    // }
    /* Set the data collected to variable that will be used publically */
    /* These values are clockwise */
    frontIR = tempIRData[0];
    rightIR = tempIRData[1];
    backIR = tempIRData[2];
    leftIR = tempIRData[3];
    /* Change to return false if all data is the same (-1) */
    if(sumArr(tempIRData, sizeof(tempIRData)/sizeof(tempIRData[0])) == -4){
        return false;
    }
    return true;
}
