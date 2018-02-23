#include <Xbee.h>

Xbees::Xbees(){
    /* Constructor */
    XSerial.begin(115200);
    resetAllData();
}

bool Xbees::isConnected(){
    if(XSerial.available()){
        timeSince.reset();
        return true;
    }
    return false;
}

void Xbees::tryConnect(){
    if(!isConnected() && timeSince.hasBeenMS(2000)){
        /* Xbee isnt connected */
        isConnected();
    }else{
        /* We assume the Xbee is connected */
        updateData();
    }
}

void Xbees::updateData(int bX, int bY, int rX, int rY, int seeing, int pos){
    ballX = bX + XBEE_CONST;
    ballY = bY + XBEE_CONST;
    robotX = rX + XBEE_CONST;
    robotY = rY + XBEE_CONST;

    seeingBall = seeing;
    knowsPosition = pos;

    if(sendTime.hasBeenMS(20)){
        sendData();
        sendTime.reset();
        readData();
    }
}

void Xbees::sendData(){
    XSerial.write(XBEE_START_BYTE);
    XSerial.write(XBEE_START_BYTE);
    XSerial.write(ballX);
    XSerial.write(ballY);
    XSerial.write(robotX);
    XSerial.write(robotY);
    XSerial.write(seeingBall);
    XSerial.write(knowsPosition);
}

void Xbees::readData(){
    while(XSerial.available() == XBEE_PACKAGE){
        uint16_t firstByte = XSerial.read();
        uint16_t secondByte = XSerial.peak();

        if(firstByte == 255 && firstByte == secondByte){
            timeSince.reset();
            XSerial.read();

            for(int i = 0; i < XBEE_PACKAGE - 2){
                dataBuf[i] = XSerial.read() - XBEE_CONST;
            }
            dataBuf[4] = XSerial.read();
            dataBuf[5] = XSerial.read();

            OballX = dataBuffer[0];
            OballY = dataBuffer[1];
            OrobtoX = dataBuffer[2];
            OrobotY = dataBuffer[3];
            OseeingBall = dataBuffer[4];
            OknowsPosition = dataBuffer[5];
        }
    }
}

void Xbees::resetAllData(){
    ballX, ballY, robotX, robotY, OballX, OballY, OrobotX, OrobotY = 65506;
    seeingBall, knowsPosition, OseeingBall, OknowsPosition = 0;
}
