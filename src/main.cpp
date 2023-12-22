#include <Arduino.h>
#include "O2Sensor.h"
#include "pressuresensor.h"

O2Sensor O2Sensor1;
PressureSensor PressureSensor1;

void setup() {
  O2Sensor1.ads.setGain(GAIN_SIXTEEN);
  O2Sensor1.ads.begin();
  Serial.begin(9600);
  Serial.println("Finished setup");
}

void loop() {
  Serial.print("O2Sensor1: ");
  Serial.println(O2Sensor1.measure());
  Serial.print("PressureSensor1: ");
  Serial.println(PressureSensor1.measure());
  delay(1000);
}

