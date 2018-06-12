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

    // BROKEN
    #if ROBOT
      //o_bot
      //                              1      2      3      4      5      6      7      8      9      10     11     12     13     14     15     16     17     18     19     20
      bool broken[LIGHTSENSOR_NUM] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
    #else
      //p2_bot
      //                              1      2      3      4      5      6      7      8      9      10     11     12     13     14     15     16     17     18     19     20
      bool broken[LIGHTSENSOR_NUM] = {false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false};
    #endif


    //THRESHOLDS
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

    //For angle countback and filtering
    double countback[NUM_COUNTBACK];
};

extern Light light;

#endif
