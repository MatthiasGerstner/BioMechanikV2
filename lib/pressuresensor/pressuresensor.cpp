#include "pressuresensor.h"

PressureSensor::PressureSensor()
{
    Serial.println("PressureSensor initialized");
    return;
}

float PressureSensor::measure()
{
    V = analogRead(Pressure_Sensor_Pin) * 4.5 / 1024;
    preasure = ((V) * 245) / 100;
    return preasure;
}