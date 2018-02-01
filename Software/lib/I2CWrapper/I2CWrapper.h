#ifndef I2CWrapper_h
#define I2CWrapper_h

#include <Arduino.h>
#include <Wire.h>
#include <Config.h>


class I2CWrapper {
public:
    I2CWrapper();
    void read(uint8_t address, uint8_t _register, uint8_t Nbytes, uint8_t* data);
    void write(uint8_t address, uint8_t _register, uint8_t data);
private:

};

#endif
