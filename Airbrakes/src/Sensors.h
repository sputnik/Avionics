#ifndef SENSORS_H
#define SENSORS_H

#include "IMUSensor.h"
#include "PTSensor.h"

class Sensors {
private:
  IMUSensor bno;
  PTSensor  pt;
public:
  // Constructor
  Sensors();

  // IMU sensor data
  void refreshIMU();
  double getAccX();
  double getAccY();
  double getAccZ();
  double getAccV();

  // PT sensor data
  double getPressure();
  double getTemperature();

  // THE DESTRUCTINATOR 3000
  ~Sensors();
};

#endif
