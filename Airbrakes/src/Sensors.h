#ifndef SENSORS_H
#define SENSORS_H

#include "Data.h"
#include <Adafruit_BNO055.h>
#include <Adafruit_MPL115A2.h>

class Sensors {
private:
  // BNO055 member variables
  Adafruit_BNO055 *bno;   // Pointer to the sensor
  imu::Vector<3> euler;   // Euler angles in m/s/s
  imu::Vector<3> acc;     // Acceleration in m/s/s
  imu::Vector<3> gravity; // Gravity in m/s/s
  imu::Vector<3> linear;  // Linear acceleration in m/s/s
  int calib[4];           // Calibration values, 0 is bad, 3 is good
  double vertAccel;       // Vertical Acceleration in g's
  double accX;            // Linear acceleration in x direction
  double accY;            // Linear acceleration in y direction
  double accZ;            // Linear acceleration in z direction

  Adafruit_MPL115A2 *pt;

public:
  // Constructor
  Sensors();
  bool begin(void);

  void updateData(Data *data);

  // IMU sensor data
  void refreshIMU(); // refreshes all info on the IMU
  // Returns the vertical acceleration in g's
  inline double getVertAccel() { return vertAccel; } // End getVertAccel

  // getAccX, getAccY, getAccZ return linear acceleration components (m/s/s)
  inline double getAccX() { return accX; } // End getAccX

  inline double getAccY() { return accY; } // End getAccY

  inline double getAccZ() { return accZ; } // End getAccZ

  // Returns the calibration of the sensor
  inline int *getCalibration() { return calib; } // End getCalibration

  // Returns the current Euler angles in degrees
  inline imu::Vector<3> getEuler() { return euler; } // End getEuler

  inline imu::Vector<3> getGravity() { return gravity; }

  inline imu::Vector<3> getLinear() { return linear; }

  inline float getTemp() { return pt->getTemperature(); }

  // Returns the pressure in kPa
  inline float getPress() { return pt->getPressure(); }

  inline void getPT(float *pres, float *temp) { pt->getPT(pres, temp); }

  // THE DESTRUCTINATOR 3000
  ~Sensors();
};

#endif
