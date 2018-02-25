#ifndef modeWrapper_h
#define modeWrapper_h

#include <Arduino.h>
#include <Common.h>
#include <Enum.h>

class modeWrapper {
public:
    modeWrapper();
    void setMode(mode option);
    mode getMode();
private:
    mode cMode = mode::unknown;
};

extern modeWrapper robotMode;

#endif
