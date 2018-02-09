#include <I2CWrapper.h>

I2CWrapper::I2CWrapper(){
    Wire.begin();
}

void I2CWrapper::read(uint8_t address, uint8_t _register, uint8_t Nbytes, uint8_t* data){
    /* Read data via I2C from a certain address */
    Wire.beginTransmission(address);
    Wire.write(_register);
    Wire.endTransmission();

    Wire.requestFrom(address, Nbytes);
    uint8_t index = 0;
    while (Wire.available()){
        data[index] = Wire.read();
        index++;
    }
}

void I2CWrapper::write(uint8_t address, uint8_t _register, uint8_t data){
    /* Write to a register address over I2C */
    Wire.beginTransmission(address);
    Wire.write(_register);
    Wire.write(data);
    Wire.endTransmission();
}
