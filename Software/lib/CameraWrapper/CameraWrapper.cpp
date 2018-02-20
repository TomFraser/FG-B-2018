#include <CameraWrapper.h>

Camera cam = Camera();

Camera::Camera(){
    /* Constructor */
}

void Camera::initSerial(){
    /* Init serial and set initial timeout */
    cameraSerial.begin(9600);
    lastCall = millis();
}

void Camera::getCamData(){
    /* Reset data in tempCamData array to -1 */
    memset(tempCamData, -1, sizeof(tempCamData));
    /* Gets camera data and set its to a number of variables */
    if(millis() - lastCall >= 20){
        while(cameraSerial.read() != 42);
        for(int i = 0; i < CAM_TRANSFER_NUM; i++){
            while(!cameraSerial.available());
            tempCamData[i] = cameraSerial.read();
        }
        cameraSerial.read();

        rawAngle = tempCamData[0];
        strength = tempCamData[1];
        _aSize = tempCamData[2];
        _aAngle = tempCamData[3];
        _dSize = tempCamData[4];
        _dAngle = tempCamData[5];

        lastCall = millis();
    }
}
