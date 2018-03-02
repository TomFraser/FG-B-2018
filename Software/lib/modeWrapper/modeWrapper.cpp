#include <ModeWrapper.h>

modeWrapper robotMode = modeWrapper();

modeWrapper::modeWrapper(){
    /* Constructor */
}

void modeWrapper::setMode(mode option){
    cMode = option;
}

void modeWrapper::setDefault(mode option){
    dMode = option;
}

void modeWrapper::_default(){
    cMode = dMode;
}

mode modeWrapper::getMode(){
    return cMode;
}
