#include <LIDARWrapper.h>

LIDAR lidar = LIDAR();

LIDAR::LIDAR(){
    /* Constructor */
}

void LIDAR::init(){
    /* Begin LIDAR serials */
    Serial1.begin(115200);
    Serial3.begin(115200);
    Serial4.begin(115200);
    Serial5.begin(115200);
}

void LIDAR::read(){
    /* Read 1st LIDAR */
    while(Serial1.available() > 8){
        int sync0 = Serial1.read();
        int sync1 = Serial1.peek();
        if (sync0 == 89 && sync1 == 89){
          Serial1.read();
          for (int i = 0; i < 4; i++){
            sensorData[i] = Serial1.read();
          }
          lidarVal[0] = sensorData[1] <<8 | sensorData[0];
        }
    }
    /* Read 2nd LIDAR */
    while(Serial3.available() > 8){
        int sync0 = Serial3.read();
        int sync1 = Serial3.peek();
        if (sync0 == 89 && sync1 == 89){
          Serial3.read();
          for (int i = 0; i < 4; i++){
            sensorData[i] = Serial3.read();
          }
          lidarVal[1] = sensorData[1] <<8 | sensorData[0];
        }
    }
    /* Read 3rd LIDAR */
    while(Serial4.available() > 8){
        int sync0 = Serial4.read();
        int sync1 = Serial4.peek();
        if (sync0 == 89 && sync1 == 89){
          Serial4.read();
          for (int i = 0; i < 4; i++){
            sensorData[i] = Serial4.read();
          }
          lidarVal[2] = sensorData[1] <<8 | sensorData[0];
        }
    }
    /* Read 4th LIDAR */
    while(Serial5.available() > 8){
        int sync0 = Serial5.read();
        int sync1 = Serial5.peek();
        if (sync0 == 89 && sync1 == 89){
          Serial5.read();
          for (int i = 0; i < 4; i++){
            sensorData[i] = Serial5.read();
          }
          lidarVal[3] = sensorData[1] <<8 | sensorData[0];
        }
    }
}
