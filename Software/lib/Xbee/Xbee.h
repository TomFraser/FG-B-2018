#ifndef Xbee_h
#define Xbee_h

#include <Config.h>
#include <Common.h>

#define XSerial Serial6

class XbeeController{
public:
    xbeeData update(xbeeData values);
private:
    xbeeData read();
    void write(xbeeData values);
    xbeeData ourData, otherData = {{65506, 65506}, {65506, 65506}, false, false};
    long lastRead = 0;

};

extern XbeeController xbee;

#endif