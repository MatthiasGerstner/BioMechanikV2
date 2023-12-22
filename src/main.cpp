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
    Controller1.menu(Controller1.currentmenuitem);
}
