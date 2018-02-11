#ifndef SPIWrapper_h
#define SPIWrapper_h

#include <Common.h>
#include <Arduino.h>
#include <SPI.h>

class SPIWrapper {
public:
    SPIWrapper();
    void initSPI();
    bool getCamData();
    bool getIRData();

    int rawAngle, strength, _aSize, _aAngle, _dSize, _dAngle;
    double frontIR, rightIR, backIR, leftIR;
private:
    uint16_t tempCamData[CAM_TRANSFER_NUM];
    uint16_t tempIRData[IR_TRANSFER_NUM];
};

extern SPIWrapper spi;

#endif
