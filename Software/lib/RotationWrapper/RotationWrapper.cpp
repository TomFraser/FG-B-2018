#include <RotationWrapper.h>

RotationWrapper rotation = RotationWrapper();

void RotationWrapper::calculateRotation(double rotation, double goal, double goalSize){
    /* Calculate the rotation from both camera and IMU */
    compassHeading = IMUController.update(rotation, 0.00, 0.00);
    compassHeading = compassHeading * IMU_MULTI;

    goalHeading = doubleMod(goal + 180, 360.0) - 180;
    goalHeading = goalController.update(goalHeading, 0.00, 0.00);
    goalHeading = goalHeading * IMU_MULTI;

    if(goal <= 0 || abs(goalHeading/IMU_MULTI) > GOAL_CUTOFF){
        gyration = signbit(compassHeading) && abs(compassHeading) > ROTATION_CUTOFF ? -ROTATION_CUTOFF : ROTATION_CUTOFF;
    }else{
        gyration = signbit(goalHeading) && abs(goalHeading > ROTATION_CUTOFF) ? -ROTATION_CUTOFF : ROTATION_CUTOFF;
    }
}

double RotationWrapper::getRotation(){
    /* Getter for rotation */
    return gyration;
}
