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
        O2_pressure_m1 = 0.209;
        Input1.waitforenter("Releas Pressure, open Lid and press enter");
        if (PressureSensor1.measure() < 1.02 && PressureSensor1.measure() > 0.98)
        {
            Serial.println("Waiting 15 seconds for sensor to stabilize");
            wait(15);
            Serial.println("Start Calibration");
            for (int i = 0; i < CALIBRATIONMEASUREMENTS; i++)
            {
                calibpoint1[i].mV_calib = O2Sensor1.measure();
                calibpoint1[i].pressure_calib = O2_pressure_m1;
                delay(100);
            }
            calibpoint1_mean.mV_calib = meanArray(1);
            calibpoint1_mean.pressure_calib = O2_pressure_m1;
            Serial.print("Mean mV: ");
            Serial.println(calibpoint1_mean.mV_calib);
            currentmenuitem = 3;
            Serial.println("-------------------------------------------");
        }
        else
        {
            Serial.println("Error: Pressure not in range");
            currentmenuitem = 2;
        }
        break;

    case 3:
        Serial.println("Preasure System with compressed air or flood with O2");
        Input1.waitforenter("Press enter when finished");
        Serial.print("Current pressure inside of pot: ");
        Serial.print(PressureSensor1.measure());
        Serial.println(" bar");
        O2_pressure_m2 = Input1.enterNumber("Enter current O2 partial pressure in bar: ");
        Serial.println("Waiting 15 seconds for sensor to stabilize");
        wait(15);
        Serial.println("Start Calibration");
        for (int i = 0; i < CALIBRATIONMEASUREMENTS; i++)
        {
            calibpoint2[i].mV_calib = O2Sensor1.measure();
            calibpoint2[i].pressure_calib = O2_pressure_m2;
            delay(100);
        }
        calibpoint2_mean.mV_calib = meanArray(2);
        calibpoint2_mean.pressure_calib = O2_pressure_m2;
        Serial.print("Mean mV: ");
        Serial.println(calibpoint2_mean.mV_calib);
        Serial.println("-------------------------------------------");
        currentmenuitem = 4;
        break;
    case 4: // calculate calibration curve
        Serial.println("Calculating calibration curve");
        O2Sensor1.calibrate(calibpoint1_mean.pressure_calib, calibpoint1_mean.mV_calib, calibpoint2_mean.pressure_calib, calibpoint2_mean.mV_calib);
        Serial.print("Calibration Curve: ");
        Serial.print(O2Sensor1.calib_param.m);
        Serial.print(" * x + ");
        Serial.println(O2Sensor1.calib_param.t);
        Serial.println("-------------------------------------------");
        currentmenuitem = 5;
        break;
    case 5: // compare measurement
        Serial.println("flood system with O2 at max pressure");
        Input1.waitforenter("Press enter when finished");
        Serial.println("Waiting 15 seconds for sensor to stabilize");
        wait(15);
        Serial.println("Start Calibration");
        for (int i = 0; i < CALIBRATIONMEASUREMENTS; i++)
        {
            measurement[i].mV_calib = O2Sensor1.measure();
            measurement[i].pressure_calib = PressureSensor1.measure();
            delay(100);
        }
        measurement_mean.mV_calib = meanArray(3);
        measurement_mean.pressure_calib = meanArray(4);
        Serial.print("Mean mV: ");
        Serial.println(measurement_mean.mV_calib);
        Serial.print("Mean pressure: ");
        Serial.println(measurement_mean.pressure_calib);
        Serial.println("-------------------------------------------");
        currentmenuitem = 6;
        break;

    case 6: // compare measurement with expected value
        O2_expected = O2Sensor1.calib_param.m * measurement_mean.pressure_calib + O2Sensor1.calib_param.t;
        deviation = (O2_expected - measurement_mean.mV_calib) / O2_expected * 100;
        Serial.print("Expected mV: ");
        Serial.println(O2_expected);
        Serial.print("Measured mV: ");
        Serial.println(measurement_mean.mV_calib);
        Serial.print("Deviation: ");
        Serial.print(deviation);
        Serial.println(" %");
        Input1.waitforenter("Press enter to restart program");
        Serial.println("-------------------------------------------");
        currentmenuitem = 1;
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
        Serial.print(seconds - i);
        Serial.print(" ");
        Serial.print('\r');
        delay(1000);
    }
    return;
}

float Controller::meanArray(int i)
{
    float sum = 0, mean = 100;
    switch (i)
    {
    case 1:

        for (int i = 0; i < CALIBRATIONMEASUREMENTS; i++)
        {
            sum = sum + calibpoint1[i].mV_calib;
        }
        mean = sum / CALIBRATIONMEASUREMENTS;
        break;
    case 2:
        for (int i = 0; i < CALIBRATIONMEASUREMENTS; i++)
        {
            sum = sum + calibpoint2[i].mV_calib;
        }
        mean = sum / CALIBRATIONMEASUREMENTS;
        break;
    case 3:

        for (int i = 0; i < CALIBRATIONMEASUREMENTS; i++)
        {
            sum = sum + measurement[i].mV_calib;
        }
        mean = sum / CALIBRATIONMEASUREMENTS;
        break;
    case 4:
        for (int i = 0; i < CALIBRATIONMEASUREMENTS; i++)
        {
            sum = sum + measurement[i].pressure_calib;
        }
        mean = sum / CALIBRATIONMEASUREMENTS;
        break;
    default:
        break;
    }
    return mean;
}