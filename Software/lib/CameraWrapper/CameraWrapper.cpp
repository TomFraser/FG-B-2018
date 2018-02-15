#include <CameraWrapper.h>

Camera::Camera(){
    /* Constructor */
}

void Camera::initSerial(){
    cameraSerial.begin(9600);
    lastCall = millis();
}

void Camera::getCamData(){
    if(millis() - lastCall >= 20){
        while(camSerial.read() != 42);
        while(!camSerial.available());
        tempCamData[0] = camSerial.read();
        while(!camSerial.available());
        tempCamData[1] = camSerial.read();
        while(!camSerial.available());
        tempCamData[2] = camSerial.read();
        while(!camSerial.available());
        tempCamData[3] = camSerial.read();
        while(!camSerial.available());
        camSerial.read();
    }
}
