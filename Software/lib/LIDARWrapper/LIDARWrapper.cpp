#include <LIDARWrapper.h>

LIDAR lidar = LIDAR();

LIDAR::LIDAR(){
    Serial.begin(115200);
    Serial1.begin(115200);
    Serial2.begin(115200);
    Serial3.begin(115200);
}

void LIDAR::read(){
    if(Serial.available() == 9){
        byteCounter = 0;
        while(byteCounter <= 9){
            sensorData[byteCounter] = Serial.read();
            byteCounter++;
        }
        values[0] = sensorData[2] << + sensorData[3];
        strengths[0] = sensorData[4] << + sensorData[5];
    }

    if(Serial1.available() == 9){
        byteCounter = 0;
        while(byteCounter <= 9){
            sensorData[byteCounter] = Serial1.read();
            byteCounter++;
        }
        values[1] = sensorData[2] << + sensorData[3];
        strengths[1] = sensorData[4] << + sensorData[5];
    }

    if(Serial2.available() == 9){
        byteCounter = 0;
        while(byteCounter <= 9){
            sensorData[byteCounter] = Serial2.read();
            byteCounter++;
        }
        values[2] = sensorData[2] << + sensorData[3];
        strengths[2] = sensorData[4] << + sensorData[5];
    }

    if(Serial3.available() == 9){
        byteCounter = 0;
        while(byteCounter <= 9){
            sensorData[byteCounter] = Serial3.read();
            byteCounter++;
        }
        values[3] = sensorData[2] << + sensorData[3];
        strengths[3] = sensorData[4] << + sensorData[5];
    }
}
