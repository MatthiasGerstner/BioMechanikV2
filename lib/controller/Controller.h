#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <Arduino.h>
#include "O2Sensor.h"
#include "pressuresensor.h"
#include "Input.h"

class Controller
{
private:
public:
    O2Sensor O2Sensor1;
    PressureSensor PressureSensor1;
    Input Input1;
    Controller();
    void menu(int menuitem);
};

#endif