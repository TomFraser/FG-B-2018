#include <CoordCalc.h>

CoordCalc::CoordCalc(){
  // init
}

/* Public Functions */
void CoordCalc::updateData(cameraData cam, lidarData lidar, double compassw){

}


/* Private Functions */
int CoordCalc::calcGoalDistanceCam(int goalArea, int goalAngle, bool attack){
  #if ROBOT
    // o_bot
    if(goalArea > 105 && goalArea <= 206){
      return -sqrt(9100-0.87*pow(goalArea-105, 2))+101;
    }
    else{
      return -1;
    }
  #else
    // p2_bot
    if(attack){
      // front thing
      if(goalArea > 99 && goalArea <= 198){
        return -1.02*sqrt(10400-1.06*pow(goalArea-99, 2))+111;
      }
      else{
        return -1;
      }
    }
    else{
      // back thing
      if(goalArea > 103 && goalArea <= 214){
        return -sqrt(9100-0.76*pow(goalArea-105, 2))+99;
      }
      else{
        return -1;
      }

    }
  #endif
}
