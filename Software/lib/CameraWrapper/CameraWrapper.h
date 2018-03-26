#ifndef CameraWrapper_h
#define CameraWrapper_h

#include <Arduino.h>
#include <Common.h>

#define cameraSerial Serial1

class Camera {
public:
    Camera();
    void initSerial();
    void getCamData();

    int rawAngle, strength, _ySize, _yAngle, _bSize, _bAngle;

private:
    long lastCall;
    uint8_t tempCamData[CAM_TRANSFER_NUM];
    uint16_t bitCombinedData[CAM_TRANSFER_NUM/2];

};

extern Camera cam;

#endif
