#ifndef Xbee_h
#define Xbee_h

#include <Config.h>
#include <Common.h>

#define XSerial Serial6

class XbeeController{
public:
    XbeeController();
    xbeeData update(xbeeData values);
    bool isConnected();
    xbeeData otherData = {{65506, 65506}, {65506, 65506}, false, false};
private:
    void resetOtherData();
    xbeeData read();
    void write(xbeeData values);
    xbeeData ourData = {{65506, 65506}, {65506, 65506}, false, false};
    long lastRead = 0;

};

extern XbeeController xbee;

#endif
