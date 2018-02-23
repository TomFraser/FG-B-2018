#ifndef Common_h
#define Common_h
#pragma once

#include <Arduino.h>
#include <Config.h>


// ulong initTime;
// int led;

bool isFrontal(int angle);

bool isFrontalLarge(int angle);

double doubleMod(double value, double maxVal);

void blink();

bool lightGateTriggered();

double fromFront(double angle);

double calculateBallConfidence(double strength, double angle);

uint16_t sumArr(uint16_t *arr);

#endif
