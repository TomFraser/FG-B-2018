#include <LIDARWrapper.h>

LIDAR lidar = LIDAR();

LIDAR::LIDAR(){
    Serial.begin(115200);
    Serial1.begin(115200);
    Serial2.begin(115200);
    Serial3.begin(115200);
}

void LIDAR::read(){
    while(Serial.available() > 8){
        int sync0 = Serial.read();
        int sync1 = Serial.peek();
        if (sync0 == 89 && sync1 == 89){
          Serial.read();
          for (int i = 0; i < 4; i++){
            sensorData[i] = Serial.read();
          }
          values[0] = 65535;
          // values[0] = sensorData[1] <<8 | sensorData[0];
          strengths[0] = sensorData[3] <<8 | sensorData[2];
        }
    }

    // while(Serial1.available() > 8){
    //     int sync0 = Serial1.read();
    //     int sync1 = Serial1.peek();
    //     if (sync0 == 89 && sync1 == 89){
    //       Serial1.read();
    //       for (int i = 0; i < 4; i++){
    //         sensorData[i] = Serial1.read();
    //       }
    //       values[1] = sensorData[1] <<8 | sensorData[0];
    //       strengths[1] = sensorData[3] <<8 | sensorData[2];
    //     }
    // }
    //
    // while(Serial2.available() > 8){
    //     int sync0 = Serial2.read();
    //     int sync1 = Serial2.peek();
    //     if (sync0 == 89 && sync1 == 89){
    //       Serial2.read();
    //       for (int i = 0; i < 4; i++){
    //         sensorData[i] = Serial2.read();
    //       }
    //       values[2] = sensorData[1] <<8 | sensorData[0];
    //       strengths[2] = sensorData[3] <<8 | sensorData[2];
    //     }
    // }
    //
    // while(Serial3.available() > 8){
    //     int sync0 = Serial3.read();
    //     int sync1 = Serial3.peek();
    //     if (sync0 == 89 && sync1 == 89){
    //       Serial3.read();
    //       for (int i = 0; i < 4; i++){
    //         sensorData[i] = Serial3.read();
    //       }
    //       values[3] = sensorData[1] <<8 | sensorData[0];
    //       strengths[3] = sensorData[3] <<8 | sensorData[2];
    //     }
    // }
}
