// This example shows how to read temperature/pressure from adafruit library
//walkthrough and code: https://learn.adafruit.com/adafruit-dps310-precision-barometric-pressure-sensor/arduino

#include "pressure.h"

//debug to figure out how to include this, maybe use setup function
Adafruit_DPS310 dps;

// Can also use SPI!
#define DPS310_CS 10 //will use I^2C (since its simpler) with arduino nano
  // Note on pin hardware: SCK = I2C SCL = A5 on arduino nano, SDI=SDA=A4, follow tutorial
  //? unsure if needed for new stm32

byte pressure= -1;//pressure in hPa 
byte temperature=-1;//degrees C, -1 placeholder

//wrapper function
void measurements(){//updates global vars with new measurements
  sensors_event_t temp_event, pressure_event;
  dps.getEvents(&temp_event, &pressure_event);//setup code

  pressure = pressure_event.pressure;//updated measurements
  temperature = temp_event.pressure;
}

void pressureCheck(){
  dps.configurePressure(DPS310_64HZ, DPS310_64SAMPLES);
  dps.configureTemperature(DPS310_64HZ, DPS310_64SAMPLES);

  while (dps.temperatureAvailable() && dps.pressureAvailable()) {
    measurements(); // wait until there's something to read
  }

}