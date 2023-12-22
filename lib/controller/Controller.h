#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <Arduino.h>
#include "O2Sensor.h"
#include "pressuresensor.h"
#include "Input.h"
#define CALIBRATIONMEASUREMENTS 100

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
public:
    O2Sensor O2Sensor1;
    PressureSensor PressureSensor1;
    Input Input1;
    int currentmenuitem = 1;
    Controller();
    void menu(int menuitem);
    void wait(int seconds);
    float meanArray();
};

#endif