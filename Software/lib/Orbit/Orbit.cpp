#include <Orbit.h>

double orbitSimple(int angle, double ratio){
    if(angle == -1 || angle == 65506){
        return 65506;
    }
    /* Simple orbit from last year for testing */
    if(ratio < 0.00 || ratio > 1.00){
        ratio = 1.00;
    }
    if(angle == -1){
        return -1.00;
    }else if(isFrontal(angle)){
        return angle < 180 ? (angle + (angle/50)) : (360-angle - (360-angle)/50);
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
        if(distance > 75){
            /* Move ball direction */
            return angle;
        }else if(distance > 50 && distance <= 75){
            /* A lil bit closer */
            return orbitSimple(angle, 0.15);
        }else if(distance > 35 && distance <= 50){
            /* Sorta orbit */
            return orbitSimple(angle, 0.3);
        }else if(distance < 35){
            /* Normal Orbit */
            return orbitSimple(angle, 0.6);
        }
    }else{
        return orbitSimple(angle, 0.6);
    }
}
