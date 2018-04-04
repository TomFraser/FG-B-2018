#ifndef Light_h
#define Light_h

#include <Arduino.h>
#include <Common.h>
#include <Structs.h>

struct cluster{
  bool exist;
  int begin;
  int end;
};

class Light{

public:
    Light();

    //Set up the light sensors
    void init();

    //Dump Light Values
    void getVals(int *);

    //Dump On White Values
    void getOnWhite(bool *);

    //Read the light sensors
    void readLight();

    // get if theres an error (if a sensor has bricked)
    bool getError();

    // update the light angle
    void updateAngle();

    lightData data;

private:
    // Function Definitions

    //Identify clusters of lightsensors seeing the Line
    void singleCluster(cluster *, int, int);

    //Find all the clusters
    void findClusters(cluster *);


    // cluster shit
    double getClusterAngle(int clusterBegin, int clusterEnd);

    // Other Stuff

    //init stuff
    #if AUTO_LIGHT
      int thresholds[LIGHTSENSOR_NUM];
    #else
      #if ROBOT
        //o_bot
        int thresholds[LIGHTSENSOR_NUM] = {471, 425, 281, 240, 328, 296, 327, 306, 578, 402, 316, 493, 351, 300, 286, 180, 106, 310, 304, 364};
      #else
        //p2_bot
        int thresholds[LIGHTSENSOR_NUM] = {231, 294, 339, 216, 221, 203, 169, 214, 350, 229, 175, 261, 227, 220, 222, 69, 182, 249, 241, 134};
      #endif
    #endif

    int lightSensors[LIGHTSENSOR_NUM];

    bool error = false;

    // bool seeingWhite[LIGHTSENSOR_NUM] = {true, true, true, true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
    bool seeingWhite[LIGHTSENSOR_NUM];

    //cluster stuff
    double lightCoords[20][2] = {
        {light1x, light1y},
        {light2x, light2y},
        {light3x, light3y},
        {light4x, light4y},
        {light5x, light5y},
        {light6x, light6y},
        {light7x, light7y},
        {light8x, light8y},
        {light9x, light9y},
        {light10x, light10y},
        {light11x, light11y},
        {light12x, light12y},
        {light13x, light13y},
        {light14x, light14y},
        {light15x, light15y},
        {light16x, light16y},
        {light17x, light17y},
        {light18x, light18y},
        {light19x, light19y},
        {light20x, light20y}
    };

    //For angle countback and filtering
    double countback[NUM_COUNTBACK];
};

extern Light light;

#endif
