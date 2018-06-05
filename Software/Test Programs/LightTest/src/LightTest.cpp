#include <Light.h>

Light Light;

int lightValues[LIGHTSENSOR_NUM];// = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool results[LIGHTSENSOR_NUM];

int threshold = 0;
int counter = 0;

int mode = 0; // 0 = raw vals, 1 = 1's and 0's, 2 = processed angle, 3 = positive only, 4 = numSensors


void setup(){
    Light.init();

    Serial.begin(9600);
}

void loop(){
  Light.readLight();
  Light.updateAngle();
  if(mode == 0){
    // === Print out raw values ===
    Light.getVals(lightValues);
    for(int i=0; i < LIGHTSENSOR_NUM; i++){
      Serial.print(lightValues[i]);

      if(lightValues[i]<10){
        Serial.print(" ");
      }
      if(lightValues[i]<100){
        Serial.print(" ");
      }
      if(lightValues[i] < 1000){
        Serial.print(" ");
      }
      Serial.print(" ");
    }
    Serial.println();
    delay(100);
  }
  else if(mode == 1){
    // // === Print out on white ===
    Light.getOnWhite(results);
    for(int i=0; i < LIGHTSENSOR_NUM; i++){
      // if(results[1] > 0){
      //   Serial.print(results[i]);
      // }
      // else{
      //   Serial.print(" ");
      // }
      Serial.print(results[i]);
      Serial.print("   ");
    }
    Serial.println();
  }
  else if(mode == 2){
    Serial.println(Light.data.angle);
  }
  else if(mode == 3){
    // // === Print out on white ===
    Light.getOnWhite(results);
    bool print = false;

    for(int i=0; i < LIGHTSENSOR_NUM; i++){
      if(results[i] > 0){
        print = true;
      }
    }

    if(print){
      for(int i=0; i < LIGHTSENSOR_NUM; i++){
        Serial.print(results[i]);
        Serial.print("   ");
      }
      Serial.println();

    }
  }
  else if(mode == 4){
    Serial.println(Light.data.numSensors);
  }
}
