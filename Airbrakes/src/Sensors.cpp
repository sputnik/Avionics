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

// gets X acceleration data
double Sensors::getAccX(){
  return bno.getAccX();
}

// gets Y acceleration data
double Sensors::getAccY(){
  return bno.getAccY();
}
// gets Z acceleration data
double Sensors::getAccZ(){
  return bno.getAccZ();
}

// gets vertical acceleration in m/s^2 data from bno
double Sensors::getAccV() {
  double accV;
  accV = bno.getVertAccel();
  return accV;
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
