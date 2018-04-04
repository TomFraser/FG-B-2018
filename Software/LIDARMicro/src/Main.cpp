#include <Arduino.h>
#include <LIDARWrapper.h>
#include <Common.h>

void setup(){
    pinMode(MISO, OUTPUT);
    pinMode(13, OUTPUT);
    /* Set up SPI Settings and Enable Interrupts */
    SPCR=(1<<SPE)|(0<<CPOL)|(0<<CPHA)|(0<<DORD)|(0<<MSTR)|(1<<SPIE);
}

void loop(){
    /* Read Lidar Sensors */
    lidar.read();
    /* Get Request Data From Master */
    uint8_t data = SPDR;
    /* Respond Based on Request Data */
    // switch(data){
    //     case 1:
    //         // SPDR = (lidar.values[0] & 0xFF); break;
    //         SPDR = 0; break;
    //     case 2:
    //         // SPDR = (lidar.values[0] >> 8); break;
    //         SPDR = 20; break;
    //     case 3:
    //         // SPDR = (lidar.values[1] & 0xFF); break;
    //         SPDR = 40; break;
    //     case 4:
    //         // SPDR = (lidar.values[1] >> 8); break;
    //         SPDR = 60; break;
    //     case 5:
    //         // SPDR = (lidar.values[2] & 0xFF); break;
    //         SPDR = 80; break;
    //     case 6:
    //         // SPDR = (lidar.values[2] >> 8); break;
    //         SPDR = 100; break;
    //     case 7:
    //         // SPDR = (lidar.values[3] & 0xFF); break;
    //         SPDR = 120; break;
    //     case 8:
    //         // SPDR = (lidar.values[3] >> 8); break;
    //         SPDR = 140; break;
    // }
    if(data == 1){
        SPDR = 20;
    }else if(data == 2){
        SPDR = 40;
    }
    /* Wait for the data to successfully transfer before continuing */
    while (!(SPSR & (1<<SPIF)));
}
