#include <Arduino.h>
// #include <SPI.h>
// #include <LIDARWrapper.h>
// #include <Common.h>

void setup(){
    pinMode(MISO, OUTPUT);
    pinMode(13, OUTPUT);
    /* Set up SPI settings and enable Interrupts */
    SPCR=(1<<SPE)|(0<<CPOL)|(0<<CPHA)|(0<<DORD)|(0<<MSTR)|(1<<SPIE);
}

void loop(){
    int data = SPDR;
    if(data == 1){
      digitalWrite(13, HIGH);
    }else if(data == 2){
      digitalWrite(13, LOW);
    }
     SPDR = 69;
     while (!(SPSR & (1<<SPIF)));
    // lidar.read();
}
