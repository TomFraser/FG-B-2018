double orbitSimple(int angle){
    /* Simple orbit from last year for testing */
    if(angle == -1){
        return -1.00;
    }else if(isFrontalLarge(angle)){
        return angle < 180 ? (angle + (angle/7500)) : (angle - (360-angle)/7500);
    }else{
        return angle < 180 ? (angle + 90) : (angle - 90);
    }
}

double orbit(int angle, int strength){
    // Complex orbit using the strength of the cam
    return 0.00;
}
