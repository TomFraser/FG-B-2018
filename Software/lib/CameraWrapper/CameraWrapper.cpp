#include <CameraWrapper.h>

Camera::Camera(){
    /* Declarations */

}

void Camera::initSPI(){
    /* Init and setup SPI */
    pinMode(CAM_SS, OUTPUT);
    SPI.begin();
    digitalWrite(CAM_SS, HIGH);
    SPI.setSCK(ALT_SCK);
    SPI.setClockDivider(SPI_CLOCK_DIV8);
}

bool Camera::getCamData(){
    /* Reset data in tempCamData array to -1 */
    memset(tempCamData, -1, sizeof(tempCamData));
    /* Request data from Camera */
    for(int i = 0; i < CAM_TRANSFER_NUM; i++){
        digitalWrite(CAM_SS, LOW);
        tempCamData[i] = SPI.transfer16(i);
        digitalWrite(CAM_SS, HIGH);
    }
    /* Set the data collected to variables that will be used publically */
    rawAngle = tempCamData[0];
    strength = tempCamData[1];
    _aSize = tempCamData[2];
    _aAngle = tempCamData[3];
    _dSize = tempCamData[4];
    _dAngle = tempCamData[5];
    return true;
}
