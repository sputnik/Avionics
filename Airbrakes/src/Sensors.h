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
  void refreshIMU(); // refreshes all info on the IMU
  double getAccX(); // gets the x-axis acceleration (m/s/s)
  double getAccY(); // gets the y-axis acceleration (m/s/s)
  double getAccZ(); // gets the z-axis acceleration (m/s/s)
  double getAccV(); // gets the vertical accleration (m/s/s)

  // PT sensor data
  double getPressure(); // gets the current air pressure (kPa)
  double getTemperature(); // gets the current temperature (C)

  // THE DESTRUCTINATOR 3000
  ~Sensors();
};

#endif
