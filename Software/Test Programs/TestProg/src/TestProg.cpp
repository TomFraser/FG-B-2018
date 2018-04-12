#include <Common.h>
#include <Config.h>

void setup(){
    Serial.begin(9600);
}

uint8_t tempCamData[CAM_TRANSFER_NUM];
uint16_t bitCombinedData[CAM_TRANSFER_NUM/2];
long lastCall;
void loop(){
    /* Reset data in tempCamData array to -1 */
    memset(tempCamData, -1, sizeof(tempCamData));
    /* Gets camera data and set its to a number of variables */
    if(millis() - lastCall >= 20 && Serial1.available() == CAM_TRANSFER_NUM){
        if(Serial1.read() == 42){
            for(int i = 0; i < CAM_TRANSFER_NUM; i++){
                while(!Serial1.available());
                tempCamData[i] = Serial1.read();
            }

            for(int i = 0; i < CAM_TRANSFER_NUM/2; i++){
                bitCombinedData[i] = (tempCamData[2*i] << 8) + tempCamData[2*i+1];
            }
        }
        Serial.println(bitCombinedData[0]);
    }
}
