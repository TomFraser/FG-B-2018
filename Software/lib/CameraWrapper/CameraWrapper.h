#ifndef CameraWrapper_h
#define CameraWrapper_h

#include <Config.h>
#include <Common.h>
#include <Arduino.h>
#include <SPI.h>

class Camera {
public:
    Camera();
    void initSPI();
    bool getCamData();
    
    int angle, rawAngle, strength, _aSize, _aAngle, _dSize, _dAngle;
private:
    uint16_t tempCamData[CAM_TRANSFER_NUM];
};

#endif
