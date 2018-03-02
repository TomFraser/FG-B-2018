#ifndef ModeWrapper_h
#define ModeWrapper_h

#include <Arduino.h>
#include <Common.h>
#include <Enum.h>

class modeWrapper {
public:
    modeWrapper();
    void setMode(mode option);
    void setDefault(mode option);
    void _default();
    mode getMode();
private:
    mode cMode = mode::unknown;
    mode dMode = mode::unknown;
};

extern modeWrapper robotMode;

#endif
