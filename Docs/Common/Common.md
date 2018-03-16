# Common



#### Library Purpose

The purpose of the **Common** library is to house functions that don't warrant a specific library or belong to a specific class. Functions defined in Common will often be used in multiple places throughout the program and libraries. It contains 1 x <*.h, .cpp*> files.



#### Library Information

The Common library has no class and therefore no constructor is called, the file is simply included.

**Dependencies**

- Arduino.h
- Config.h



#### Functions

```c++
bool isFrontal(int angle);
```

**Parameters**

The isFrontal function takes an argument of type **int** which is the current angle of the ball in polar coordinates.

The isFrontal function returns a **boolean** stating whether the ball is within the front 30 degrees (± 15).



**Duty**

The isFrontal functions converts polar coordinates to an angle from the front of the robot and determines if it is within a range.



```c++
bool isFrontalLarge(int angle);
```

**Parameters**

The isFrontal function takes an argument of type **int** which is the current angle of the ball in polar coordinates.

The isFrontal function returns a **boolean** stating whether the ball is within the front 60 degrees (± 30).



**Duty**

The isFrontal functions converts polar coordinates to an angle from the front of the robot and determines if it is within a range.



```c++
double doubleMod(double value, double maxVal);
```

**Parameters**

The doubleMod function takes in two arguments of type **double** which are the value to be modded and the max value allowed.

The doubleMod function return a **double** that is the modded double value.



**Duty**

The doubleMod function applies modulus to the float value given.



```c++
void blink();
```

**Parameters**

The blink function takes in no arguments and returns nothing.



**Duty**

The blink function blinks the LED attached to pin 13 on the Teensy3.5 changing the state every second.



```c++
bool lightGateTriggered();
```

**Parameters**

The lightGateTriggered function takes in no arguments.

The lightGateTriggered function returns a **boolean** that is the result of the light gate being broken.



**Duty**

The lightGateTriggered function checks if the laser light gate has been broken by the ball. If the laser light gate is broken, the ball is currently in the ball capture zone of the robot.



```c++
double fromFront(double angle);
```

**Parameters**

The fromFront function takes in an argument of type **double** which is the current polar coordinate angle of the ball

The fromFront function returns a **double** that is angle of the the ball from the front of the robot.



**Duty**

The fromFront function converts the given angle in polar coordinates to an angle from the front of the robot.



```c++
double calculateBallConfidence(double strength, double angle);
```

**Parameters**

The calculateBallConfidence function takes in two arguments of type **double** that are the current strength of the ball and the angle of the ball.

The calculateBallConfidence returns a **double** that is the robots confidence of collecting the ball.



**Duty**

The calculateBallConfidence function determines how confident the robot will be in its ability to collect the ball based on the relative angle and distance to the ball.



```c++
uint16_t sumArr(uint16_t arr[], int size);
```

**Paramteres**

The sumArr function takes in two arguments, a **pointer** and **integer** which are the pointer address for an array and the size of the array.

The sumArr function returns a value of type **u_int16t** that is the sum of all elements of the array.



**Duty**

The sumArr function adds all the elements of an array together and returns the result.