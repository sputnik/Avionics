#include "PTSensor.h"

PTSensor::PTSensor()
{
  pt = new Adafruit_MPL115A2();
  pt->begin();
}
