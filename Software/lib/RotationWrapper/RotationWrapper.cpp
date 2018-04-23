#include <RotationWrapper.h>

void RotationWrapper::calculateRotation(double rotation, double goal, double goalSize, double target){
    /* Calculate the rotation from both camera and IMU */
    compassHeading = IMUController.update(rotation, target, 0.00);
    // compassHeading = compassHeading * IMU_MULTI;

    // if(goal != 65506){
    //     goalHeading = doubleMod(goal + 180, 360.0) - 180;
    //     goalHeading = goalHeading * IMU_MULTI;
    // }else{
    //     goalHeading = 65506;
    // }
    //
    // if(goalHeading != 65506){
    //     gyration = goalHeading;
    // }else{
        gyration = compassHeading;
    // }
}

double RotationWrapper::getRotation(){
    /* Getter for rotation */
    return gyration;
}
