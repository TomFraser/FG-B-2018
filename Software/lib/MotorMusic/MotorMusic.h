#ifndef MotorMusic_h
#define MotorMusic_h

#include <Songs.h>
#include <Timer.h>
#include <Arduino.h>

void motorMusic(String song, int trackNum);
void playSong(uint16_t songData[], const uint16_t songLength, const uint8_t tempo);
// void playSongAsync(uint16_t songData[], uint16_t songLength, uint8_t tempo);

#endif