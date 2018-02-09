#include <SPIWrapper.h>

SPIWrapper::SPIWrapper(SPIDevice device){
    _device = device;
}

void SPIWrapper::beginSlave(){
    if(_device == SPIDevice::CortexM4){
        /* Teensy Slave */

    }else if(_device == SPIDevice::ATMega328P){
        /* ATMega Slave */
        pinMode(MISO, OUTPUT);

        SPCR |= bit(SPE);
        SPCR |= bit(SPIE);
    }
}

void SPIWrapper::beginMaster(){
    if(_device == SPIDevice::CortexM4){
        /* Teensy Master */

    }else if(_device == SPIDevice::ATMega328P){
        /* ATMega Master */

    }
}
