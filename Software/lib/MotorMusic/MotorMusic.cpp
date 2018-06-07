#include <MotorMusic.h>
#include <Musics.h>

Timer RNATimer = Timer(0);

uint16_t Freq8[] = {4186, 4435, 4699, 4978, 5274, 5588, 5920, 6272, 6645, 7040, 7459, 7902};

void motorMusic(String song, int trackNum){
    if(song == "RNA"){
        /* RNA, tempo of 4 */
        playSong(RNA, sizeof(RNA)/sizeof(uint16_t), 3);
    }else if(song == "Pirates"){
        /* Pirates */
        playSong(Pirates, sizeof(Pirates)/sizeof(uint16_t), 2);
    }else if(song == "Africa"){
        /* We are the champions */
        playSong(Africa, sizeof(Africa)/sizeof(uint16_t), 2);
    }else if(song == "Faded"){
        playSong(Faded, sizeof(Faded)/sizeof(uint16_t), 7);
    }else if(song == "Darude"){
        playSong(Darude, sizeof(Darude)/sizeof(uint16_t), 4);
    }else if(song == "Canada"){
        playSong(Canada, sizeof(Canada)/sizeof(uint16_t), 2);
    }else if(song == "MI"){
        playSong(MI, sizeof(MI)/sizeof(uint16_t), 4);
    }else if(song == "ANA"){
        playSong(ANA, sizeof(ANA)/sizeof(uint16_t), 6);
    }else if(song == "LORD"){
        playSong(LORD, sizeof(LORD)/sizeof(uint16_t), 2);
    }else if(song == "MARCH"){
        playSong(MARCH, sizeof(MARCH)/sizeof(uint16_t), 1);
    }
}

void playSong(uint16_t songData[], const uint16_t songLength, const uint8_t tempo){
    for(uint16_t  x = 0; x < songLength; x++){
        uint16_t data = pgm_read_word((uint16_t *)&songData[x]);
        if((data & 0xF) == 0xF){
            writeFreq(19000);
        }else{
            int freq = pgm_read_word(&Freq8[data&0xF]) / (1<<(8 - (data>>4 & 0xF)));
            writeFreq(freq);
        }    
        int duration = data >> 8;
        while(duration--) delay(tempo);
    }
}

// void playSongAsync(uint16_t songData[], uint16_t songLength, uint8_t tempo){
//     // trackOneCount = 0;
//     uint16_t data = pgm_read_word((uint16_t *)&songData[trackOneCount]);
//     if((data & 0xF) == 0xF){
//         writeFreq(19000);
//     }else{
//         int freq = pgm_read_word(&Freq8[data&0xF]) / (1<<(8 - (data>>4 & 0xF)));
//         writeFreq(freq);
//     }
//     int duration = data >> 8;
//     if(RNATimer.hasBeenMS(tempo)){
//         duration--;
//         RNATimer.reset();
//     }
//     if(duration-- == 0){
//         trackOneCount++;
//     }
//     if(trackOneCount == songLength){
//         trackOneCount = 0;
//     }
// }

