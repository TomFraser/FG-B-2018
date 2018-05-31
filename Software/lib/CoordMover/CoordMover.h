#ifndef CoordMover_h
#define CoordMover_h

#include <Arduino.h>
#include <Common.h>
#include <Structs.h>

#define TARGET_LIST_LENGTH 20
#define COMPLETED_THRESHOLD 5

class CoordMover{

public:
    CoordMover();
    moveControl calcMove();

    // target list stuff
    void clearTargetList();
    void setTargetList(coordinate* toSet);

    bool completed = true;


private:
    moveControl goToCoords(coordinate target);
    coordinate current;
    coordinate targetList[TARGET_LIST_LENGTH];


};
#endif
