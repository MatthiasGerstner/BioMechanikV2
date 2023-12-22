#include "O2Sensor.h"

O2Sensor::O2Sensor()
{
    
    Serial.println("O2Sensor initialized");
    return;
}

float O2Sensor::measure()
{
    adc_O2 = ads.readADC_SingleEnded(O2SensorPin);
    mV_O2 = ads.computeVolts(adc_O2);
    mV_O2 = mV_O2 * 1000;
    return mV_O2;
}