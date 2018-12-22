// Class file for pressure and temperature sensor
#include "PTSensor.h"

// Constructs the sensor
PTSensor::PTSensor() {
  pt = new Adafruit_MPL115A2();
  pt->begin();
} // End Constructor

// Destructs the object to clear up space
PTSensor::~PTSensor() {
  delete pt;
} // End destructor
