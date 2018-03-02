#ifndef Xbee_h
#define Xbee_h

#include <Arduino.h>
#include <Common.h>
#include <Timer.h>
#define XSerial Serial1

class Xbees {
public:
    Xbees();
    bool isConnected();
    void tryConnect();
    void updateData(int bX, int bY, int rX, int rY, int seeing, int pos);

    /* Recieve Data */
    int OballX, OballY, OrobotX, OrobotY, OseeingBall, OknowsPosition;
    
private:
    void sendData();
    void readData();
    void resetAllData();

    /* Send Data */
    int ballX, ballY, robotX, robotY, seeingBall, knowsPosition;

    /* Timer for disconnected timeout */
    Timer timeSince = Timer(0);
    /* Timer for xbee send time */
    Timer sendTime = Timer(0);

    uint8_t dataBuf[XBEE_PACKAGE - 2];
};

extern Xbees xbee;

#endif
