// Header file for the imu

#ifndef IMUSENSOR_H_
#define IMUSENSOR_H_
#include <Adafruit_BNO055.h>

class IMUSensor {
public:
  // Constructs the sensor object
  IMUSensor();

  // Updates the data
  void updateData();

  // Returns the vertical acceleration in g's
  inline double getVertAccel() {
    return vertAccel;
  } // End getVertAccel

  // Returns the calibration of the sensor
  inline int * getCalibration() {
    return calib;
  } // End getCalibration

  // Returns the current Euler angles in degrees
  inline imu::Vector<3> getEuler() {
    return euler;
  } // End getEuler

  inline imu::Vector<3> getGravity() {
    return gravity;
  }

  inline imu::Vector<3> getLinear() {
    return linear;
  }

  // Destructs the sensor
  ~IMUSensor();

private:
  Adafruit_BNO055 * bno; // Pointer to the sensor
  imu::Vector<3> euler; // Euler angles in m/s/s
  imu::Vector<3> acc; // Acceleration in m/s/s
  imu::Vector<3> gravity; // Gravity in m/s/s
  imu::Vector<3> linear; // Linear acceleration in m/s/s
  int calib[4]; // Calibration values, 0 is bad, 3 is good
  double vertAccel; // Vertical Acceleration in g's
};
#endif
