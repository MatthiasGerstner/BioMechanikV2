#include "pressuresensor.h"

PressureSensor::PressureSensor()
{
    Serial.println("PressureSensor initialized");
    return;
}

float PressureSensor::measure()
{
    V = analogRead(Pressure_Sensor_Pin) * 5.00 / 1024;
    pressure = (((V-Offset) * 250) * 0.01) + 1.019;
    return pressure;
}