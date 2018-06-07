#include <Xbee.h>

XbeeController xbee = XbeeController();

xbeeData XbeeController::update(xbeeData values){
    if(millis() > lastRead + 20){
        read();
        write(values);
    }
}

xbeeData XbeeController::read(){
    if(XSerial.available() > 0){
        Serial.println(XSerial.read());
    }
    // uint8_t buf[XBEE_PACKAGE - 2];
    // while(XSerial.available() >= XBEE_PACKAGE){
    //     uint8_t firstByte = XSerial.read();
    //     uint8_t secondByte = XSerial.peek();

    //     if(firstByte == XBEE_START_BYTE && secondByte == XBEE_START_BYTE){
    //         XSerial.read();

    //         for(int i = 0; i < XBEE_PACKAGE - 4; i++){
    //             buf[i] = XSerial.read() - XBEE_CONST;
    //         }
    //         buf[4] = XSerial.read();
    //         buf[5] = XSerial.read();
    //     }
    // }
    // for(int i = 0; i < XBEE_PACKAGE - 2; i++){
    //     Serial.println(buf[i]);
    // }
    // Serial.println();
    // lastRead = millis();
}

void XbeeController::write(xbeeData values){
    values.ballCoords.x = values.ballCoords.x == 65506 ? 0 : values.ballCoords.x;
    values.ballCoords.y = values.ballCoords.y == 65506 ? 0 : values.ballCoords.y;
    values.robotCoords.x = values.robotCoords.x == 65506 ? 0 : values.robotCoords.x;
    values.robotCoords.y = values.robotCoords.y == 65506 ? 0 : values.robotCoords.y;

    XSerial.write(XBEE_START_BYTE);
    XSerial.write(XBEE_START_BYTE);
    XSerial.write(uint8_t(values.ballCoords.x));
    XSerial.write(uint8_t(values.ballCoords.y));
    XSerial.write(uint8_t(values.robotCoords.x));
    XSerial.write(uint8_t(values.robotCoords.y));
    XSerial.write(uint8_t(values.seesBall));
    XSerial.write(uint8_t(values.knowsPosition));
}