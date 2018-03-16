# Ball Manager



#### Library Purpose

The purpose of the *Ball Manager* library is to control all physical components of the robot that act upon the game ball. It contains 1 x <*.h, .cpp*> files.



#### Library Information

The constructor for the class is called in the *main.cpp* file.

**Dependencies**

* Arduino.h
* ECUDriver.h
* Timer.h
* Enum.h



#### Class Structure

The library follows the following class structure:

```c++
class BallManager {
public:
    BallManager();
    bool controlBall(double ballConfidence);
    void kickBall();
private:
    ECUDriver backspin = ECUDriver(BACKSPIN_PIN);
    Timer timeSinceKick = Timer(0);

    solenoidMode mode;
};
```



#### Functions

```c++
bool controlBall(double ballConfidence)
```

The controlBall function takes an argument of type **double** which is the robots calculated chance of collecting the ball.

The controlBall function returns a **boolean** stating whether the robot has the ball.



The controlBall function determines the speed that the dribbler will run at as well as determining if we currently have possession of the ball. It also notifies the rest of the program whether the solenoid is ready to kick the ball.



```c++
void kickBall();
```

The kickBall function takes in no arguments and returns no value.



The kickBall function first slows the dribbler then activates the solenoid on the robot kicking the ball.