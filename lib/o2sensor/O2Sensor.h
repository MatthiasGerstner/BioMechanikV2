#ifndef O2SENSOR_H
#define O2SENSOR_H
#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include <SPI.h>

#define O2SensorPin 0

class O2Sensor
{
private:
    int adc_O2;
public:
    Adafruit_ADS1115 ads;
    float mV_O2;
    O2Sensor();
    float measure();
};

#endif