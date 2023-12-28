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

void O2Sensor::calibrate(float x1, float y1, float x2, float y2){
    if (x1 == x2){
        Serial.println("Error: x1 == x2");
        return;
    }
    calib_param.m = (y2 - y1) / (x2 - x1);
    calib_param.t = y1 - calib_param.m * x1;
    return;
}