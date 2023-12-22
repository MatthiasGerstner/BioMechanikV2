#include "Controller.h"

Controller::Controller()
{
    Serial.println("Controller initialized");
    return;
}

void Controller::menu(int menuitem)
{
    switch (menuitem)
    {
    case 1:
        Input1.waitforenter("Press enter to start");
        currentmenuitem = 2;
        break;
    case 2:
        Input1.waitforenter("Releas Pressure and open Lid");
        if (PressureSensor1.measure() < 1.02 && PressureSensor1.measure() > 0.98)
        {
            Serial.println("Waiting 15 seconds for sensor to stabilize");
            wait(1);
            for (int i = 0; i < CALIBRATIONMEASUREMENTS; i++)
            {
                calibpoint1[i].mV_calib = O2Sensor1.measure();
                calibpoint1[i].pressure_calib = 20.9;
                delay(100);
            }
            calibpoint1_mean.mV_calib = meanArray();
            calibpoint1_mean.pressure_calib = 20.9;
            Serial.println(calibpoint1_mean.mV_calib);
            currentmenuitem = 3;
        }
        else
        {
            Serial.println("Error: Pressure not in range");
            currentmenuitem = 2;
        }
        break;
    case 3:
        break;
    case 4:
        break;
    default:
        break;
    }
    return;
}

void Controller::wait(int seconds)
{
    for (int i = 0; i < seconds; i++)
    {
        Serial.println(seconds - i);
        delay(1000);
    }
    return;
}

float Controller::meanArray()
{
    float sum = 0, mean = 0;
    for (int i = 0; i < CALIBRATIONMEASUREMENTS; i++)
    {
        sum = sum + calibpoint1[i].mV_calib;
    }
    mean = sum / CALIBRATIONMEASUREMENTS;
    return mean;
}