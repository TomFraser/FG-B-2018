#include <Arduino.h>
#include <SPI.h>
// #include <LIDARWrapper.h>
#include <Common.h>

// bool state = false;

void func(){
    // SPDR = 1;
    // while (!(SPSR & (1<<SPIF)));
}

void setup(){
    // Serial.begin(9600);
    pinMode(MISO, OUTPUT);
    SPCR |= bit (SPE);
    attachInterrupt(digitalPinToInterrupt(13), func, FALLING);
    interrupts();
}

void loop(){
    // lidar.read();
}

// ISR(SPI_STC_vect){
//     int command = SPDR;
//     int data = -1;
//     switch(command){
//         case 1:
//             data = 1;
//         case 2:
//             data = 2;
//         case 3:
//             data = 3;
//         case 4:
//             data = 4;
//     }
//     SPDR = data;
//     while (!(SPSR & (1<<SPIF))){
//     }
//     return SPDR;
// }
