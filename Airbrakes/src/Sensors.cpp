#include "Arduino.h"
#include "Wire.h"

#include "IMUSensor.h"
#include "PTSensor.h"

#include "Sensors.h"

// Constructor
Sensors::Sensors() {
  // the setup (not sure if this is right)
  bno = IMUSensor();
  pt = PTSensor();
}

// updates the data stored on the IMU
void Sensors::refreshIMU(){
  bno.updateData();
}

// gets vertical acceleration in m/s^2 data from bno
double Sensors::getAccV() {
  double AccV;
  AccV = bno.getVertAccel();
  return AccV;
}

// gets pressure in kPa from pt
double Sensors::getPressure() {
  double pressure;
  pressure = pt.getPress();
  return pressure;
}

// gets the temperature in C from pt
double Sensors::getTemperature() {
  double temperature;
  temperature = pt.getPress();
  return temperature;
}

// Deconstructor
Sensors::~Sensors() {
  //TODO
}
