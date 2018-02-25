#include <Light.h>

Light::Light(){
    //init
    pinMode(LIGHT_1, INPUT);
    pinMode(LIGHT_2, INPUT);
    pinMode(LIGHT_3, INPUT);
    pinMode(LIGHT_4, INPUT);
    pinMode(LIGHT_5, INPUT);
    pinMode(LIGHT_6, INPUT);
    pinMode(LIGHT_7, INPUT);
    pinMode(LIGHT_8, INPUT);
    pinMode(LIGHT_9, INPUT);
    pinMode(LIGHT_10, INPUT);
    pinMode(LIGHT_11, INPUT);
    pinMode(LIGHT_12, INPUT);
    pinMode(LIGHT_13, INPUT);
    pinMode(LIGHT_14, INPUT);
    pinMode(LIGHT_15, INPUT);
    pinMode(LIGHT_16, INPUT);
    pinMode(LIGHT_17, INPUT);
    pinMode(LIGHT_18, INPUT);
    pinMode(LIGHT_19, INPUT);
    pinMode(LIGHT_20, INPUT);

    lightSensors[0] = LIGHT_1;
    lightSensors[1] = LIGHT_2;
    lightSensors[2] = LIGHT_3;
    lightSensors[3] = LIGHT_4;
    lightSensors[4] = LIGHT_5;
    lightSensors[5] = LIGHT_6;
    lightSensors[6] = LIGHT_7;
    lightSensors[7] = LIGHT_8;
    lightSensors[8] = LIGHT_9;
    lightSensors[9] = LIGHT_10;
    lightSensors[10] = LIGHT_11;
    lightSensors[11] = LIGHT_12;
    lightSensors[12] = LIGHT_13;
    lightSensors[13] = LIGHT_14;
    lightSensors[14] = LIGHT_15;
    lightSensors[15] = LIGHT_16;
    lightSensors[16] = LIGHT_17;
    lightSensors[17] = LIGHT_18;
    lightSensors[18] = LIGHT_19;
    lightSensors[19] = LIGHT_20;

    for(int i = 0; i < NUM_COUNTBACK; i++){
      countback[i] = -1;
    }

}


//====================Getter Dump Functions===========================
void Light::getVals(int *vals){
  for(int i = 0; i < LIGHTSENSOR_NUM; i++){
      vals[i] = analogRead(lightSensors[i]);
  }
}

void Light::getOnWhite(bool *vals){
  for(int i=0; i < LIGHTSENSOR_NUM; i++){
    vals[i] = seeingWhite[i];
  }
}

bool Light::getError(){
  return error;
}

// ================== Cluster Caluation Things ===================
double Light::getClusterAngle(int clusterBegin, int clusterEnd){
  return (fmod((clusterEnd - clusterBegin)/2.0 + clusterBegin, LIGHTSENSOR_NUM)/(LIGHTSENSOR_NUM-1))*360.0;
}

//=============================Other Functions=====================
void Light::init(){
    #if AUTO_LIGHT
      // set calubrations based on init values
      delay(500);
      for(int i=0; i < LIGHTSENSOR_NUM; i++){
        thresholds[i] = 0;
      }

      for(int t=0; t < LIGHT_CALB_LOOPS; t++){
        int vals[LIGHTSENSOR_NUM];
        getVals(vals);
        for(int i=0; i < LIGHTSENSOR_NUM; i++){
          thresholds[i] += vals[i];
        }
      }

      for(int i=0; i < LIGHTSENSOR_NUM; i++){
        thresholds[i] /= LIGHT_CALB_LOOPS;
        thresholds[i] += THRESHOLD_OFFSET;
      }
    #endif
}

void Light::readLight(){
    int tempCount = 0;
    for(int i = 0; i < LIGHTSENSOR_NUM; i++){
      if(thresholds[i] != -1){
        int val = analogRead(lightSensors[i]);
        if(val >= thresholds[i]){
            seeingWhite[i] = true;
            tempCount++;
        }
        else{
            seeingWhite[i] = false;
        }
      }
      else{
        seeingWhite[i] = false;
      }
    }
    numSensors = tempCount;
}

int Light::getNumSensors(){
  return numSensors;
}

//[0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0]
void Light::singleCluster(cluster *returnClus, int startNum, int begin){
  if(seeingWhite[startNum%LIGHTSENSOR_NUM]){
    if(seeingWhite[(startNum+1)%LIGHTSENSOR_NUM]){
      singleCluster(returnClus, startNum+1, begin);
    }
    else{
      returnClus->exist = true;
      returnClus->begin = begin;
      returnClus->end = startNum;
      return;
    }
  }
  else{
    returnClus->exist = false;
    return;
  }
}

//foundClusters is a cluster array of length maxNumClusters
void Light::findClusters(cluster *foundClusters){
  cluster temp = {false, 0, 0};
  for(int i = 0; i < maxNumClusters; i++){
    foundClusters[i] = temp;
  }

  int index = 0;
  int num = 0;
  while(num < LIGHTSENSOR_NUM){
    cluster c;
    singleCluster(&c, num, num);
    if(c.exist){
      foundClusters[index] = c;
      index++;
      num = c.end+1;
    }
    else{
      num++;
    }
  }

  index --; //index is now at the last index of clusters

  if(foundClusters[index].end > LIGHTSENSOR_NUM-1 && foundClusters[0].begin == 0){
    // // then we have a wrapped cluster so make the first cluster invalid
    foundClusters[0] = {true, -1, -1};
  }



  // print all found clusters
  // for(int i=0; i<maxNumClusters; i++){
  //   Serial.print(foundClusters[i].begin); Serial.print(" "); Serial.print(foundClusters[i].end); Serial.print(" | ");
  // }
  // Serial.println();
}

double Light::getAngle(){
    // get all the current clusters
    cluster foundClusters[maxNumClusters];
    findClusters(foundClusters);

    double directionAngle;

    if(!foundClusters[0].exist){ // if we found no clusters
      directionAngle = 65506;
    }
    else{
      cluster clus1;
      cluster clus2;
      cluster clus3;

      if(foundClusters[0].begin != -1){
        clus1 = foundClusters[0];
        clus2 = foundClusters[1];
        clus3 = foundClusters[2];
      }
      else{
        clus1 = foundClusters[1];
        clus2 = foundClusters[2];
        clus3 = foundClusters[3];
      }

      double lineAngle = 60;
      double angle1 = getClusterAngle(clus1.begin, clus1.end);
      double angle2 = getClusterAngle(clus2.begin, clus2.end);
      double angle3 = getClusterAngle(clus3.begin, clus3.end);

      // Serial.println(angle1);
      // Serial.println(angle2);
      // Serial.println(angle3);
      // Serial.println();

      if(!clus1.exist){
        directionAngle = 65506;
      }
      else{
        if(!clus2.exist){
          // only have 1 cluster
          lineAngle = angle1;
        }
        else if(!clus3.exist){
          // only have 2 clusters
          lineAngle = angleBetween(angle1, angle2) <= 180 ? midAngleBetween(angle1, angle2) : midAngleBetween(angle2, angle1);
        }
        else{
          // have 3 clusters
          double angleDiff12 = angleBetween(angle1, angle2);
          double angleDiff23 = angleBetween(angle2, angle3);
          double angleDiff31 = angleBetween(angle3, angle1);

          double biggestAngle = max(angleDiff12, max(angleDiff23, angleDiff31));

          if(angleDiff12 == biggestAngle){
            lineAngle = midAngleBetween(angle2, angle1);
          }
          else if(angleDiff23 == biggestAngle){
            lineAngle = midAngleBetween(angle3, angle2);
          }
          else{
            lineAngle = midAngleBetween(angle1, angle3);
          }
        }

        directionAngle = fmod(lineAngle + 180, 360); //make it the opposite direction
        // Serial.println(lineAngle);
        // Serial.println();
      }
    }

    double countbackVal = directionAngle;

    // check the countback for if all the values are greater than 0 if we are greater than 0
    if(directionAngle != 65506){
      bool allGood = true;
      for(int i=0; i < NUM_COUNTBACK; i++){
        if(countback[i] < 0){
          allGood = false;
        }
      }
      if(!allGood){
        directionAngle = 65506;
      }
    }

    // for(int i=0; i<NUM_COUNTBACK; i++){
    //   Serial.print(i); Serial.print(" "); Serial.println(countback[i]);
    //   Serial.println();
    // }


    for(int i=0; i<NUM_COUNTBACK-1; i++){
      countback[i+1] = countback[i];
    }

    countback[0] = countbackVal;

    return directionAngle;
}
