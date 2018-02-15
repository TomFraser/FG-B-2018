#ifndef CameraWrapper_h
#define CameraWrapper_h

#define cameraSerial Serial1

class Camera {
public:
    Camera();
    void initSerial();
    void getCamData();

    int rawAngle, strength, _aSize, _aAngle, _dSize, _dAngle;

private:
    long lastCall;
    uint8_t tempCamData[CAM_TRANSFER_NUM];

};

#endif
