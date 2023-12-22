#ifndef O2SENSOR_H
#define O2SENSOR_H
#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include <SPI.h>

#define O2SensorPin 0

struct Geradenparameter{
    float m;
    float b;
};


class O2Sensor
{
private:
    int adc_O2;

public:
    Geradenparameter calib_param;
    Adafruit_ADS1115 ads;
    float mV_O2;
    O2Sensor();
    float measure(); // returns mV
    void calibrate(float x1, float y1, float x2, float y2); // x: O2 pressure, y: mV
};
#endif