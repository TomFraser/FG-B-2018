#ifndef CameraWrapper_h
#define CameraWrapper_h

#include <Arduino.h>
#include <Common.h>
#include <Structs.h>

#define cameraSerial Serial1

class Camera {
public:
    Camera();
    void initSerial();
    void getCamData(bool attackingYellow);

    cameraData data;

private:
    uint8_t tempCamData[CAM_TRANSFER_NUM];
    uint16_t bitCombinedData[CAM_TRANSFER_NUM/2];

    int ballAngleBuf[CAM_BUFFER_NUM];
    int ballDistBuf[CAM_BUFFER_NUM];
};

extern Camera cam;

#endif
