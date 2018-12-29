// Class file for imu sensor

#include "IMUSensor.h"
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

// Constructor, initializes the pointer
IMUSensor::IMUSensor() {
  bno = new Adafruit_BNO055(55, 0x28);
} // end constructor

// Updates the data from the imu
void IMUSensor::updateData() {
  // Getting new vectors for euler angles, gravity, accelerometer, and linear
  // acceleration
  euler = bno->getVector(Adafruit_BNO055::VECTOR_EULER); // Unit: degrees
  gravity = bno->getVector(Adafruit_BNO055::VECTOR_GRAVITY); // Unit: m/s/s
  acc = bno->getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER); // Unit: m/s/s
  linear = bno->getVector(Adafruit_BNO055::VECTOR_LINEARACCEL); // Unit: m/s/s

  // Calculates the new vertical acceleration
  vertAccel = (gravity[0]*linear[0] + gravity[1]*linear[1] + gravity[2]*linear[2])/9.81;

  // Linear acceleration components
  accX = linear[0];
  accY = linear[1];
  accZ = linear[2];

  // Gets the calibration for the sensor; 0 = bad, 3 = good
  uint8_t system, gyro, accel, mag = 0;
  bno->getCalibration(&system, &gyro, &accel, &mag);
  calib[0] = system;
  calib[1] = gyro;
  calib[2] = accel;
  calib[3] = mag;
} // end updateData

// Self-Destruction
IMUSensor::~IMUSensor() {
  delete bno;
  // delete euler;
  // delete gravity; // oops
  // delete acc;
  // delete linear;
  // delete vertAccel;
  delete calib;
} // End Destruction
