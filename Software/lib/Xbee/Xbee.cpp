#include <Xbee.h>

Xbees::Xbees(){
    /* Constructor */
}

Xbees::init(){
    XBEESERIAL.begin(9600);
    robot = GOALIE;
    resetData();
}

Xbees::updateCoordinateData(int ballX, int ballY, int robotX, int robotY, int canSeeBall, int knowsOwnCoords){
    _ballX = ballX + XBEE_ADDED_CONST;
    _ballY = ballY + XBEE_ADDED_CONST;
    _robotX = robotX + XBEE_ADDED_CONST;
    _robotY = robotY + XBEE_ADDED_CONST;
    _canSeeBall = canSeeBall;
    _knowsOwnCoords = knowsOwnCoords;
    if(millis() > lastSendTime + 20){
        dataSend();
    }
    return dataRead();
}

void Xbees::dataSend(){
    XBEESERIAL.write(XBEE_START_BYTE);
    XBEESERIAL.write(XBEE_START_BYTE);
    XBEESERIAL.write(_ballX);
    XBEESERIAL.write(_ballY);
    XBEESERIAL.write(_robotX);
    XBEESERIAL.write(_robotY);
    XBEESERIAL.write(_canSeeBall);
    XBEESERIAL.write(_knowsOwnCoords);
}

void Xbees::dataRead(){
    if(XBEESERIAL.available() == XBEE_PACKAGE_SIZE){
        uint8_t firstByte = XBEESERIAL.read();
        uint8_t secondByte = XBEESERIAL.peak();

        if(firstByte == 255 && firstByte == secondByte){
            XBEESERIAL.read();

            for (int i = 0; i < XBEE_PACKAGE_SIZE - 4; i++) {
                dataBuffer[i] = XBEESERIAL.read() - XBEE_ADDED_CONST;
            }
            dataBuffer[4] = XBEESERIAL.read();
            dataBuffer[5] = XBEESERIAL.read();

            otherBallX = dataBuffer[0];
            otherBallY = dataBuffer[1];
            otherX = dataBuffer[2];
            otherY = dataBuffer[3];
            otherCanSeeBall = dataBuffer[4];
            otherKnowsOwnCoords = dataBuffer[5];
        }
    }
}
