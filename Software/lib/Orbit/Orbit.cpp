#include <Orbit.h>

double orbitSimple(int angle, double ratio){
    /* Simple orbit from last year for testing */
    if(ratio < 0.00 || ratio > 1.00){
        ratio = 1.00;
    }
    if(angle == -1){
        return -1.00;
    }else if(isFrontal(angle)){
        return angle < 180 ? (angle + (angle/50) * ratio) : (angle - (360-angle)/50 * ratio);
    }else{
        return angle < 180 ? (angle + (90 * ratio)) : (angle - (90 * ratio));
    }
}

double orbit(int angle, int distance){
    /* Ensure that we actually have a distance */
    if(angle == -1 || angle == 65506){
        return 65506;
    }
    if(distance != NULL){
        if(distance >= BIG_DISTANCE){
            /* Move ball direction */
            return angle;
        }else if(distance < BIG_DISTANCE && distance >= SHORT_DISTANCE){
            /* Sorta orbit */
            orbitSimple(angle, 0.5);
        }else if(distance < SHORT_DISTANCE){
            /* Normal Orbit */
            orbitSimple(angle, 1.0);
        }
    }else{
        return orbitSimple(angle, 1.0);
    }
}
