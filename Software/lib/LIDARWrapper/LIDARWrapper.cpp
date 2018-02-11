#include <LIDARWrapper.h>

LIDAR lidar = LIDAR();

LIDAR::LIDAR(){
    Serial.begin(115200);
    Serial1.begin(115200);
    Serial2.begin(115200);
    Serial3.begin(115200);
}

void LIDAR::read(){
    bytesReady = Serial.available();
    if(bytesReady == 9){
        byteCounter = 0;
        while(bytesReady > 0){
            sensorData[byteCounter] = Serial.read();
            byteCounter++;
        }
        values[0] = sensorData[2] << + sensorData[3];
        strengths[0] = sensorData[4] << + sensorData[5];
    }

    bytesReady = Serial1.available();
    if(bytesReady == 9){
        byteCounter = 0;
        while(bytesReady > 0){
            sensorData[byteCounter] = Serial1.read();
            byteCounter++;
        }
        values[1] = sensorData[2] << + sensorData[3];
        strengths[1] = sensorData[4] << + sensorData[5];
    }

    bytesReady = Serial2.available();
    if(bytesReady == 9){
        byteCounter = 0;
        while(bytesReady > 0){
            sensorData[byteCounter] = Serial2.read();
            byteCounter++;
        }
        values[2] = sensorData[2] << + sensorData[3];
        strengths[2] = sensorData[4] << + sensorData[5];
    }

    bytesReady = Serial3.available();
    if(bytesReady == 9){
        byteCounter = 0;
        while(bytesReady > 0){
            sensorData[byteCounter] = Serial3.read();
            byteCounter++;
        }
        values[3] = sensorData[2] << + sensorData[3];
        strengths[3] = sensorData[4] << + sensorData[5];
    }
}
