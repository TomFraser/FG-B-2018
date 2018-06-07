#include <Xbee.h>

XbeeController xbee = XbeeController();

XbeeController::XbeeController(){
    XSerial.begin(9600);
    resetOtherData();
}

bool XbeeController::isConnected(){
    return millis() < lastWrite + 1000;
}

xbeeData XbeeController::update(xbeeData values){
    read();
    if(millis() > lastWrite + 10){
        write(values);
    }
    if(!isConnected()){
        resetOtherData();
    }
}

void XbeeController::resetOtherData(){
    otherData.ballCoords.x = 65506;
    otherData.ballCoords.y = 65506;
    otherData.robotCoords.x = 65506;
    otherData.robotCoords.y = 65506;
    otherData.seesBall = false;
    otherData.knowsPosition = false;
}

xbeeData XbeeController::read(){
    // resetOtherData();
    uint16_t buf[XBEE_PACKAGE - 2] = {65506, 65506, 65506, 65506, false, false};
    while(XSerial.available() >= XBEE_PACKAGE){
        uint8_t firstByte = XSerial.read();
        uint8_t secondByte = XSerial.peek();

        if(firstByte == XBEE_START_BYTE && secondByte == XBEE_START_BYTE){
            XSerial.read();

            for(int i = 0; i < XBEE_PACKAGE - 4; i++){
                buf[i] = XSerial.read() - XBEE_CONST;
            }
            buf[4] = XSerial.read();
            buf[5] = XSerial.read();
        }

        otherData.ballCoords.x = buf[0];
        otherData.ballCoords.y = buf[1];
        otherData.robotCoords.x = buf[2];
        otherData.robotCoords.y = buf[3];
        otherData.seesBall = bool(buf[4]);
        otherData.knowsPosition = bool(buf[5]);
        lastWrite = millis();
    }
}

void XbeeController::write(xbeeData values){
    values.ballCoords.x = values.ballCoords.x == 65506 ? 0 : values.ballCoords.x;
    values.ballCoords.y = values.ballCoords.y == 65506 ? 0 : values.ballCoords.y;
    values.robotCoords.x = values.robotCoords.x == 65506 ? 0 : values.robotCoords.x;
    values.robotCoords.y = values.robotCoords.y == 65506 ? 0 : values.robotCoords.y;

    XSerial.write(XBEE_START_BYTE);
    XSerial.write(XBEE_START_BYTE);
    XSerial.write(uint8_t(values.ballCoords.x) + XBEE_CONST);
    XSerial.write(uint8_t(values.ballCoords.y) + XBEE_CONST);
    XSerial.write(uint8_t(values.robotCoords.x) + XBEE_CONST);
    XSerial.write(uint8_t(values.robotCoords.y) + XBEE_CONST);
    XSerial.write(uint8_t(values.seesBall));
    XSerial.write(uint8_t(values.knowsPosition));
}
