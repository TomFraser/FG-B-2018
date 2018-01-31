#include <CameraWrapper.h>

Camera::Camera(){
    //Declarations

}

void Camera::initSPI(){
    //Init and setup SPI
    pinMode(CAM_SS, OUTPUT);
    SPI.begin();
    digitalWrite(CAM_SS, HIGH);
    SPI.setSCK(ALT_SCK);
    SPI.setClockDivider(SPI_CLOCK_DIV8);
}

bool Camera::getCamData(){
    //Reset data in tempCamData array to -1
    memset(tempCamData, -1, sizeof(tempCamData));
    //Request data from Camera
    for(int i = 0; i < CAM_TRANSFER_NUM; i++){
        digitalWrite(CAM_SS, LOW);
        tempCamData[i] = SPI.transfer16(i);
        digitalWrite(CAM_SS, HIGH);
    }
    //Set the data collected to variables
    angle = tempCamData[0];
    rawAngle = tempCamData[1];
    strength = tempCamData[2];
    _aSize = tempCamData[3];
    _aAngle = tempCamData[4];
    _dSize = tempCamData[5];
    _dAngle = tempCamData[6];
}
