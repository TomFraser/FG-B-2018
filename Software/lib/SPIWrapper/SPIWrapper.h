#ifndef SPIWrapper_h
#define SPIWrapper_h

#include <SPI.h>
#include <t3spi.h>

enum SPIDevice {
    CortexM4,
    ATMega328P
};

class SPIWrapper {
public:
    SPIWrapper(SPIDevice device){};

    void beginSlave();
    void beginMaster();

    uint8_t sendData(uint8_t data);
    uint8_t recieveData(uint8_t data);
private:
    SPIDevice _device;

};

#endif
