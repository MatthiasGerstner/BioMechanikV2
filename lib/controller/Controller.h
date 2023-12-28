#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <Arduino.h>
#include "O2Sensor.h"
#include "pressuresensor.h"
#include "Input.h"
#define CALIBRATIONMEASUREMENTS 20

struct CalibrationPoint
{
    float mV_calib;       // y-Axis
    float pressure_calib; // x-Axis
};

class Controller
{
private:
    CalibrationPoint calibpoint1[CALIBRATIONMEASUREMENTS], calibpoint2[CALIBRATIONMEASUREMENTS];
    CalibrationPoint calibpoint1_mean, calibpoint2_mean;
    CalibrationPoint measurement[CALIBRATIONMEASUREMENTS];
    CalibrationPoint measurement_mean;
    float O2_pressure_m2,O2_pressure_m1;
    float deviation, O2_expected;
public:
    O2Sensor O2Sensor1;
    PressureSensor PressureSensor1;
    Input Input1;
    int currentmenuitem = 1;
    Controller();
    void menu(int menuitem);
    void wait(int seconds);
    float meanArray(int i);
};

#endif