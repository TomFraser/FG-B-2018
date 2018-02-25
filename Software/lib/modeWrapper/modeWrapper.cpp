#include <modeWrapper.h>

modeWrapper robotMode = modeWrapper();

modeWrapper::modeWrapper(){
    /* Constructor */
}

void modeWrapper::setMode(mode option){
    cMode = option;
}

mode modeWrapper::getMode(){
    return cMode;
}
