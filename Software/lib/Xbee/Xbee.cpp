#include <Xbee.h>

Xbees xbee = Xbees();

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

    }
}

void Xbees::updateData(xbeeData data){
    ballX = data.ballCoords.x + XBEE_CONST;
    ballY = data.ballCoords.y + XBEE_CONST;
    robotX = data.robotCoords.x + XBEE_CONST;
    robotY = data.robotCoords.y + XBEE_CONST;

    seeingBall = data.seesBall;
    knowsPosition = data.knowsPosition;

    if(isConnected()){
        if(sendTime.hasBeenMS(20)){
            sendData();
            sendTime.reset();
            readData();
        }
    }else{
        tryConnect();
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
    while(XSerial.available() >= XBEE_PACKAGE){
        uint16_t firstByte = XSerial.read();
        uint16_t secondByte = XSerial.peek();

        if(firstByte == 255 && firstByte == secondByte){
            timeSince.reset();
            XSerial.read();

            for(int i = 0; i < XBEE_PACKAGE - 2; i++){
                dataBuf[i] = XSerial.read() - XBEE_CONST;
            }
            dataBuf[4] = XSerial.read();
            dataBuf[5] = XSerial.read();

            xData.ballCoords.x = dataBuf[0];
            xData.ballCoords.y = dataBuf[1];
            xData.robotCoords.x = dataBuf[2];
            xData.robotCoords.x = dataBuf[3];
            xData.seesBall = dataBuf[4];
            xData.knowsPosition = dataBuf[5];
        }else{
            /* The data isnt synced. Flush all Serial data */
            for(int i = 0; i < XSerial.available(); i++){
                XSerial.read();
            }
        }
    }
}

void Xbees::resetAllData(){
    xData = {{65506, 65506}, {65506, 65506}, false, false};
    ballX, ballY, robotX, robotY = 65506;
    seeingBall, knowsPosition = false;
}
