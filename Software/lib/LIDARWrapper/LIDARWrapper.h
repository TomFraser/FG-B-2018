#ifndef LIDARWrapper_h
#define LIDARWrapepr_h

#include <Arduino.h>

class LIDAR {
public:
    LIDAR();
    void init();
    void read();
    uint16_t lidarVal[4];
private:
    uint8_t sensorData[9];
    int bytesReady = 0;
    int byteCounter = 0;
};

extern LIDAR lidar;

#endif
