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

  double getAccX();
  double getAccY();
  double getAccZ();
  double getAccV();
  double getVelX();
  double getVelY();
  double getVelZ();
  double getVelV();
  double getPressure();
  double getTemperature();

  // THE DESTRUCTINATOR 3000
  ~Sensors();
};

#endif
