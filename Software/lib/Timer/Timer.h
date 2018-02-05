#ifndef Timer_h
#define Timer_h

#include <Arduino.h>

class Timer {
public:
    Timer(int mode);

    void reset();
    void stop();
    long getTime();
    bool hasBeenMS(long microseconds);

private:
    int timerMode;
    long _iTime, _fTime, _tDiff;

};

#endif
