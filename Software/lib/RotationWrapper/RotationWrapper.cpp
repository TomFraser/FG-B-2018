#include <RotationWrapper.h>

RotationWrapper::calculateRotation(double rotation, double goal, double goalSize){
    compassHeading = rotation * IMU_MULTI;
    compassHeading = pidController.update(heading, 0.00, 0.00);

    goalHeading = ((goal + 180)%360)-180;
    goalHeading = goalHeading * IMU_MULTI;

    //  TODO Do more here
}
