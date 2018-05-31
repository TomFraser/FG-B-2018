#ifndef CoordMover_h
#define CoordMover_h

#include <Arduino.h>
#include <Common.h>
#include <Structs.h>
#include <PID.h>

#define TARGET_LIST_LENGTH 20
#define COMPLETED_THRESHOLD 10

class CoordMover{

public:
    CoordMover();
    void update(coordinate current_);
    moveControl calcMove();

    // target list stuff
    void clearTargetList();
    void setTargetList(coordinate toSet[], int size);

    bool completed = true;


private:
    moveControl goToCoords(coordinate target);
    coordinate current;
    coordinate targetList[TARGET_LIST_LENGTH];

    // PIDs
    PID goToCoordsPID = PID(-1.00, 0.0, 0.0, 0.00);


};
#endif
