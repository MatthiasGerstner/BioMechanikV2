#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H
#include <Arduino.h>
#define Pressure_Sensor_Pin A1

class PressureSensor
{
private:
    float V;
public:
    float preasure;
    PressureSensor();
    float measure();
};

#endif