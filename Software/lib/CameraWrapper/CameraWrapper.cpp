#include <CameraWrapper.h>

Camera cam = Camera();

Camera::Camera(){
    /* Constructor */
    // init buffers with empty
    for(int i=0; i<CAM_BUFFER_NUM; i++){
        ballAngleBuf[i] = 65506;
        ballDistBuf[i] = 65506;
    }
}

void Camera::initSerial(){
    /* Init serial and set initial timeout */
    cameraSerial.begin(9600);
}

void Camera::getCamData(bool attackingYellow){
    /* Reset data in tempCamData array to -1 */
    memset(tempCamData, -1, sizeof(tempCamData));
    /* Gets camera data and set its to a number of variables */
    if(cameraSerial.available() >= CAM_TRANSFER_NUM+1){
        if(cameraSerial.read() == 42){
            for(int i = 0; i < CAM_TRANSFER_NUM; i++){
                tempCamData[i] = cameraSerial.read();
            }

            for(int i = 0; i < CAM_TRANSFER_NUM/2; i++){
                bitCombinedData[i] = (tempCamData[2*i] << 8) + tempCamData[2*i+1];
            }


            data.yGoalAngle = bitCombinedData[2];
            data.yGoalStrength = bitCombinedData[3];
            data.bGoalAngle = bitCombinedData[4];
            data.bGoalStrength = bitCombinedData[5];
            data.attackingYellow = attackingYellow;

            /* ============= Ball Buffer ============= */
            // update buffer (buff is FIFO - end is most recent)

            // shift everything up one
            for(int i=0; i<CAM_BUFFER_NUM-1;i++){
                ballAngleBuf[i] = ballAngleBuf[i+1];
                ballDistBuf[i] = ballDistBuf[i+1];
            }

            // add in the newest one at the end
            ballAngleBuf[CAM_BUFFER_NUM-1] = bitCombinedData[0];
            ballDistBuf[CAM_BUFFER_NUM-1] = bitCombinedData[1];

            if(bitCombinedData[0] == 65506 || bitCombinedData[1] == 65506){ // ball angle or ball strength
                // find the mode (that isnt 65506)
                int cntA = 0;
                int maxA = 0;
                int cntD = 0;
                int maxD = 0;
                int modeAng = 65506;
                int modeDist = 65506;

                for(int i=0; i<CAM_BUFFER_NUM; i++){
                    if(ballAngleBuf[i] != 65506 && ballDistBuf[i] != 65506){

                        cntA = 0;
                        cntD = 0;

                        for(int j=i; j<CAM_BUFFER_NUM; j++){
                            if(ballAngleBuf[j] == ballAngleBuf[i]){
                                cntA++;
                            }

                            if(ballDistBuf[j] == ballDistBuf[i]){
                                cntD++;
                            }
                        }

                        if(cntA >= maxA){
                            maxA = cntA;
                            modeAng = ballAngleBuf[i];
                        }

                        if(cntD >= maxD){
                            maxD = cntD;
                            modeDist = ballDistBuf[i];
                        }
                    }
                }

                data.ballAngle = modeAng;
                data.ballStrength = modeDist;

            } else {
                data.ballAngle = bitCombinedData[0];
                data.ballStrength = bitCombinedData[1];
            }



        }else{
            /* Cam Serial Not Ready, Just loop instead of waiting */
        }
    }else{
      /* Wait for the serial buffer to fill up completly */
    }
}
