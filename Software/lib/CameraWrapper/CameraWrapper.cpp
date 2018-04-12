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

void Camera::getCamData(bool attackingYellow){
    /* Reset data in tempCamData array to -1 */
    memset(tempCamData, -1, sizeof(tempCamData));
    /* Gets camera data and set its to a number of variables */
    if(millis() - lastCall >= 20 && cameraSerial.available() >= CAM_TRANSFER_NUM){
        if(cameraSerial.read() == 42){
            for(int i = 0; i < CAM_TRANSFER_NUM; i++){
                while(!cameraSerial.available());
                tempCamData[i] = cameraSerial.read();
            }

            for(int i = 0; i < CAM_TRANSFER_NUM/2; i++){
                bitCombinedData[i] = (tempCamData[2*i] << 8) + tempCamData[2*i+1];
            }


            data.ballAngle = bitCombinedData[0];
            data.ballStrength = bitCombinedData[1];
            data.yGoalAngle = bitCombinedData[2];
            data.yGoalStrength = bitCombinedData[3];
            data.bGoalAngle = bitCombinedData[4];
            data.bGoalStrength = bitCombinedData[5];
            data.attackingYellow = attackingYellow;

            lastCall = millis();
        }else{
            /* Cam Serial Not Ready, Just loop instead of waiting */
        }
    }else{
      /* Wait for time or for the serial buffer to fill up completly */
    }
}
