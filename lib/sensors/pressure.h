
#ifndef ALTITUDE_HEADER
#define ALTITUDE_HEADER

#include <Arduino.h>
#include <Adafruit_DPS310.h>//arduino yay

//void measurements();//altitude measures
void pressureCheck();

extern byte pressure;
extern byte temperature;

#endif

