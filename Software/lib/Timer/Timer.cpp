#include <Timer.h>

Timer::Timer(int mode){
    timerMode = mode;
}

void Timer::reset(){
    /* Reset the initial time for the timer */
    _iTime = millis();
}

void Timer::stop(){
    /* Get the final time for the timer */
    _fTime = millis();
}

long Timer::getTime(){
    /* Calculate the difference between the initial and final time of the timer */
    _tDiff = _fTime - _iTime;
    return _tDiff;
}

bool Timer::hasBeenMS(long microseconds){
    /* Check if the timer difference has been longer than the input */
    _tDiff = _fTime - _iTime;
    if(_tDiff >= microseconds){
        return true;
    }
    return false;
}
