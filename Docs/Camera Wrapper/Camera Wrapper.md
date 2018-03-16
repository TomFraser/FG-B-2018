# Camera Wrapper



#### Library Purpose

The purpose of the **Camera Wrapper** library is to receive data from the OpenMV7 Camera via Serial and modify the data into the required form. It contains 1 x <*.h, .cpp*> files.



#### Library Information

The constructor for the class is called in the library header file.

**Dependencies**

- Arduino.h
  - Serial.h
- Common.h



#### Class Structure

The library follows the following class structure:

```c++
class Camera {
public:
    Camera();
    void initSerial();
    void getCamData();

    int rawAngle, strength, _aSize, _aAngle, _dSize, _dAngle;

private:
    long lastCall;
    uint8_t tempCamData[CAM_TRANSFER_NUM];

};
```



#### Functions

```c++
void initSerial();
```

**Parameters**

The initSerial functions takes in no arguments and returns no value.



**Duty**

The initSerial function begins the OpenMV7 Serial port and sets the last transmission time to the current time.

```c++
void getCamData();
```

**Parameters**

The getCamData function takes in no arguments and returns no value.



**Duty**

The getCamData function requests the Serial data from the camera and sorts it into accessible data.