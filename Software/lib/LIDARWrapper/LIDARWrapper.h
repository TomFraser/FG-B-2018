#ifndef LIDARWrapper_h
#define LIDARWrapepr_h

#include <Arduino.h>

class LIDAR {
public:
    LIDAR();
    void read();
    uint16_t values[4];
    uint16_t strengths[4];
private:
    uint8_t sensorData[9];
    int bytesReady = 0;
    int byteCounter = 0;
};

extern LIDAR lidar;

#endif
