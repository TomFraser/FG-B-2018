#include <LightTracker.h>

LightTracker::LightTracker(){
  // init
}

int LightTracker::getSpeed(){
  return speed;
}

double LightTracker::getDirection(){
  return direction;
}

bool LightTracker::getNormalGameplay(){
  return normalGameplay;
}

bool LightTracker::getSeeingLine(){
  return wasSeeingLine;
}

double LightTracker::calulateBounds(double lightAngle, double ballAngle){
  if((mod(lightAngle + 180, 360) - ballAngle) > 0 && (mod(lightAngle + 180, 360) - ballAngle) < 180){
    // need to move on upper bound
    return mod(lightAngle + SLIDE_ANGLE, 360);
  }
  else{
    // lower bound
    return mod(lightAngle - SLIDE_ANGLE, 360);
  }
}

// Light tracker now takes in only abs directions and returns an absolute direction
void LightTracker::update(double absLight, double absMove, double moveSpeed, double absRawBall, int numSensors){
    bool tempGameplay = false;
    if(absLight != 65506.00){
      // if we can see the line

      if(!wasSeeingLine){
        // just started seeing the line
        lineInitDirection = absLight;
      }

      lastAngle = absLight;
      wasSeeingLine = true;

      if(smallestAngleBetween(lineInitDirection, absLight) < ANGLE_CUTOFF){
        // we might have moved a bit (ie maybe hit a corner or something) - set a new heading
        lineInitDirection = absLight;
        wasSeeingLine = true;


        if(absMove == 65506.00){
          // if we dont have any directions -> stop on line
          #if ENABLE_DEPTH
            // push us to the right depth
            speed = numSensors > DEPTH_THRESH ? DEPTH_SPEED : SPEED_ON_LINE; //speed on line is stop
          #else
            speed = SPEED_ON_LINE;
          #endif

          direction = lineInitDirection;
        }
        else if(absRawBall == 65506.00 || smallestAngleBetween(lineInitDirection, absRawBall) < 90){
          // no ball or ball in field, do normal slide stuff on absMove

          if(smallestAngleBetween(lineInitDirection, absMove) < SLIDE_ANGLE){
            // not within the angle of a slide -> just go at move angle
            speed = moveSpeed;
            direction = absMove;
            tempGameplay = true;
          }
          else if(smallestAngleBetween(lineInitDirection, absMove) < STOP_BOUND){
            // not within stop -> do tha slide
            speed = SPEED_SLIDE;
            direction = calulateBounds(absLight, absMove);
          }
          else{
            // stop
            #if ENABLE_DEPTH
              // push us to the right depth
              speed = numSensors > DEPTH_THRESH ? DEPTH_SPEED : SPEED_ON_LINE; //speed on line is stop
            #else
              speed = SPEED_ON_LINE;
            #endif

            direction = lineInitDirection;
          }

        }
        else{
          // ball is outside the field, deal with raw ball
          if(smallestAngleBetween(lineInitDirection, absRawBall) < SLIDE_ANGLE){
            // not within the angle of a slide -> just go at move angle
            speed = moveSpeed;
            direction = absMove;
            tempGameplay = true;
          }
          else if(smallestAngleBetween(lineInitDirection, absRawBall) < STOP_BOUND){
            // not within stop -> do tha slide
            speed = SPEED_SLIDE;
            direction = calulateBounds(absLight, absRawBall);
          }
          else{
            // stop
            #if ENABLE_DEPTH
              // push us to the right depth
              speed = numSensors > DEPTH_THRESH ? DEPTH_SPEED : SPEED_ON_LINE; //speed on line is stop
            #else
              speed = SPEED_ON_LINE;
            #endif

            direction = lineInitDirection;
          }
        }
      }
      else{
        speed = SPEED_OVER_LINE;
        // flipped over the line, this is priority
        direction = lineInitDirection;
      }
    }
    else if(wasSeeingLine == true){
      // we were seeing the line and now were not
      if(smallestAngleBetween(lineInitDirection, lastAngle) < 90){
        // exited on the correct side of the line

        // reset line memeory
        wasSeeingLine = false;
        lineInitDirection = 0;

        // normal gameplay
        speed = moveSpeed;
        direction = absMove;
        tempGameplay = true;
      }
      else{
        // oops, out on the wrong side - this is priority

        // dont reset line memeory cause that will get changed if we hit the
        // line

        speed = SPEED_OVER_LINE;
        // go back in
        direction = lineInitDirection;

      }
    }
    else{
      // cant see line and wasnt seeing line - just do normal gameplay
      speed = moveSpeed;
      direction = absMove;
      tempGameplay = true;
    }

    normalGameplay = tempGameplay;
}
