#include "GPSSensor.h"

GPSSensor::GPSSensor()
{
  gps = new  TinyGPSPlus();
} // end constructor

GPSSensor::~GPSSensor()
{
  delete gps;
} // end destructor
