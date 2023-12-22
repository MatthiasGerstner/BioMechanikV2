#include <Arduino.h>
#include "Controller.h"
#define MENUITEMS 10

Controller Controller1;

void setup()
{
  Controller1.O2Sensor1.ads.setGain(GAIN_SIXTEEN);
  Controller1.O2Sensor1.ads.begin();
  Serial.begin(9600);
  Serial.println("Finished setup");
}

void loop()
{
  for (int i = 0; i < MENUITEMS; i++)
  {
    Controller1.menu(i);
  }
  Controller1.Input1.waitforenter("Press enter to restart process");
}
