#ifndef Xbee_h
#define Xbee_h

#include <Arduino.h>
#include <Common.h>

class Xbees {
public:
    Xbees();
    void init();
    bool updateCoordinateData(int ballX, int ballY, int robotX, int robotY, int canSeeBall, int knowsOwnCoords);

    int otherBallX, otherBallY, otherX, otherY;
    int otherCanSeeBall, otherKnowsOwnCoord
private:
    bool dataRead();
    bool dataSend();

};

#endif
