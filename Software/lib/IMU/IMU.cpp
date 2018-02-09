#include <IMU.h>

void IMU::init(){
    /* Init and write to the buffers */
    I2C.write(IMU_ADDRESS, 29, 0x06);
    I2C.write(IMU_ADDRESS, 26, 0x06);
    I2C.write(IMU_ADDRESS, 27, GYRO_FULL_SCALE_2000_DPS);
    I2C.write(IMU_ADDRESS, 28, ACC_FULL_SCALE_2_G);
    I2C.write(IMU_ADDRESS, 0x37, 0x02);
    I2C.write(MAG_ADDRESS, 0x0A, 0x16);
}

double IMU::calibrate(){
    /* Calibrate the sensor at the begining of the program */
    read();
    delay(IMU_CALIBRATION);
    double reading = 0;
    for(int i = 0; i < IMU_CALIBRATION_NUM; i++){
        reading += (double)read();
    }
    calibration = reading/IMU_CALIBRATION_NUM;
    return calibration;
}

double IMU::read(){
    /* Read the compass sensor */
    uint8_t buffer[2];
    I2C.read(IMU_ADDRESS, 0x47, 2, buffer);
    uint16_t gz = buffer[0] << 8 | buffer[1];
    return convertRawGyro(gz);
}

void IMU::update(){
    /* Calculate the heading */
    double reading = (double) read();
    currentTime = micros();
    heading += (4*((double)(currentTime - prevTime) / 1000000.0) * (reading - calibration));
    heading = doubleMod(heading, 360.0);
    prevTime = currentTime;
}

double IMU::getHeading(){
    /* Return the current heading */
    return heading > 180 ? (heading - 360) : heading;
}
