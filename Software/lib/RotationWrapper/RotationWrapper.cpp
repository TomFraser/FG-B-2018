#include <RotationWrapper.h>

RotationWrapper rotation = RotationWrapper();

void RotationWrapper::calculateRotation(double rotation, double goal, double goalSize){
    /* Calculate the rotation from both camera and IMU */
    compassHeading = IMUController.update(rotation, 0.00, 0.00);

    // if(goal != 65506){
    //     goalHeading = doubleMod(goal + 180, 360.0) - 180;
    //     goalHeading = goalHeading * IMU_MULTI;
    // }else{
    //     goalHeading = 65506;
    // }
    //
    // if(goalHeading != 65506){
    //     if(signbit(compassHeading) && abs(compassHeading) > ROTATION_CUTOFF){
    //         gyration = -ROTATION_CUTOFF;
    //     }else if(abs(compassHeading) > ROTATION_CUTOFF){
    //         ROTATION_CUTOFF;
    //     }
    // }else{
        gyration = compassHeading;
    // }
}

double RotationWrapper::getRotation(){
    /* Getter for rotation */
    return gyration;
}
