#include <Arduino.h>
// #include <SPI.h>
// #include <LIDARWrapper.h>
// #include <Common.h>

void func(){ //THIS IS NOT BEING CALLED!, SO INTERRUPT IS FUCKED
    SPDR = 0;
    // while (!(SPSR & (1<<SPIF)));
    // return SPDR;
}

void setup(){
    pinMode(MISO, OUTPUT);
    pinMode(13, INPUT);
    /* Set up SPI settings and enable Interrupts */
    SPCR=(1<<SPE)|(0<<CPOL)|(0<<CPHA)|(1<<DORD)|(0<<MSTR);
    attachInterrupt(digitalPinToInterrupt(13), func, FALLING);
    interrupts();
}

void loop(){
    // SPDR = 0;
    // lidar.read();
    // digitalWrite(13, HIGH);
    // delay(1000);
    // digitalWrite(13, LOW);
    // delay(1000);
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
