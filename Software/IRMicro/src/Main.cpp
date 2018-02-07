#include <Arduino.h>
#include <SPI.h>

volatile byte pos;
volatile bool process;

void setup(){
    Serial.begin(9600);
    pinMode(MISO, OUTPUT);
    SPCR |= _BV(SPE);
    SPI.attachInterrupt();
}

void loop(){
    digitalWrite(13, HIGH);
}

ISR(SPI_STC_vect){
    int c = SPDR;
    int data = 3;
    SPDR = data;
    while (!(SPSR & (1<<SPIF))){
    };
    return SPDR;
}
