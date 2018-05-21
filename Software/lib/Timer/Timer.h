#ifndef Timer_h
#define Timer_h

#include <Arduino.h>

class Timer {
public:
    Timer(int mode);

    void reset();
    long getTime();
    bool hasBeenMS(long milliseconds);

private:
    int timerMode;
    long _iTime, _fTime, _tDiff;

};

#endif
