#include <CoordMover.h>

CoordMover::CoordMover(){
  // init clear target list
  clearTargetList();
}

/* Public Functions */
void CoordMover::update(coordinate current_){
    current = current_;
}

moveControl CoordMover::calcMove(){
    // get the current target from the list
    coordinate currTarget = targetList[0];

    // Serial.print(current.x); Serial.print(" "); Serial.println(current.y);
    // Serial.print(currTarget.x); Serial.print(" "); Serial.println(currTarget.y);

    completed = false;

    if(currTarget.x == 65506 && currTarget.y == 65506){
        // there are no more instructions currently -> we've completed them all
        completed = true;
        return {65506, 0, false, 0};
    }

    // update until theres an instruction that we haven't completed yet
    while(abs(currTarget.x-current.x) < COMPLETED_THRESHOLD && abs(currTarget.y-current.y) < COMPLETED_THRESHOLD){
        // if we're here we've completed the current target - pop that one and shift all the others up
        for(int i=0; i < TARGET_LIST_LENGTH - 1; i++){
            targetList[i] = targetList[i+1];
        }
        targetList[TARGET_LIST_LENGTH] = {65506, 65506};

        // get the current target from the list
        currTarget = targetList[0];

        if(currTarget.x == 65506 && currTarget.y == 65506){
            // there are no more instructions currently -> we've completed them all
            completed = true;
            return {65506, 0, false, 0};
        }
    }

    return goToCoords(currTarget);
}

// target array control
void CoordMover::clearTargetList(){
    for(int i=0; i < TARGET_LIST_LENGTH; i++){
        targetList[i] = {65506, 65506};
    }
}


void CoordMover::setTargetList(coordinate toSet[], int size){
    clearTargetList();
    for(int i=0; i < size; i++){
        targetList[i] = toSet[i];
    }
}

/* Private Functions */
moveControl CoordMover::goToCoords(coordinate target){
    moveControl moveReturn = {65506,
                              0,
                              false,
                              0};

    if(current.x != 65506 && current.y != 65506){
        // we know where we are! go for it
        coordinate delta = {target.x - current.x, target.y - current.y};
        double distance = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
        // maybe add a distance cutoff
        moveReturn.direction = atan2(delta.x, delta.y) * radToAng;
        moveReturn.direction = doubleMod(-moveReturn.direction - 90, 360) + 90;
        moveReturn.speed = goToCoordsPID.update(distance, 0.00, 0.00);
    } else if(current.x != 65506) {
        // we know only horizontal
        int diff = target.x - current.x;
        moveReturn.direction = diff > 0 ? 90 : 270;
        moveReturn.speed = goToCoordsPID.update(abs(diff), 0.00, 0.00);
    } else if(current.y != 65506){
        // for some godforsaken reason we only know vertical
        int diff = target.y - current.y;
        moveReturn.direction = diff > 0 ? 0 : 180;
        moveReturn.speed = goToCoordsPID.update(abs(diff), 0.00, 0.00);
    }

    return moveReturn;
}
