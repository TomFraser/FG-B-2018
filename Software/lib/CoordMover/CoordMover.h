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
    void setTargetList(coordinate toSet[], int size, int rotToSet[]);

    bool completed = true;


private:
    moveControl goToCoords(coordinate target, int targetRot);
    coordinate current;
    coordinate targetList[TARGET_LIST_LENGTH];
    coordinate data = {65506, 65506};
    int targetRotationList[TARGET_LIST_LENGTH];
    int currRotation;

    // PIDs
    PID goToCoordsPID = PID(-2.00, 0.0, -0.1, 0.00);


};
#endif

