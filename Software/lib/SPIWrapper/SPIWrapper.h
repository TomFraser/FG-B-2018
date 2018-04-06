#ifndef SPIWrapper_h
#define SPIWrapper_h

#include <Common.h>
#include <Arduino.h>
#include <SPI.h>

class SPIWrapper {
public:
    SPIWrapper();
    void initSPI();
    void getIRData();

    lidarData lidars;
private:
    uint16_t tempIRData[IR_TRANSFER_NUM];
};

extern SPIWrapper spi;

#endif
