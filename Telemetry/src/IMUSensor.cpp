#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_BNO055.h"
#include "utility/imumaths.h"
#include "IMUSensor.h"

IMUSensor::IMUSensor(int32_t pinUsed, uint8_t address)
{
  bno = new Adafruit_BNO055(pinUsed, address);
}

// Updates the data from the imu
void IMUSensor::updateData()
{
  euler = bno->getVector(Adafruit_BNO055::VECTOR_EULER); // Unit: degrees
  gravity = bno->getVector(Adafruit_BNO055::VECTOR_GRAVITY); // Unit: m/s/s
  acc = bno->getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER); // Unit: m/s/s
  linear = bno->getVector(Adafruit_BNO055::VECTOR_LINEARACCEL); // Unit: m/s/s

  vertAccel = (gravity[0]*linear[0] + gravity[1]*linear[1] + gravity[2]*linear[2])/9.81;

  uint8_t system, gyro, accel, mag = 0;
  bno->getCalibration(&system, &gyro, &accel, &mag);
  calib[0] = system;
  calib[1] = gyro;
  calib[2] = accel;
}

// Calculates the vertical acceleration by taking the dot product of the
// gravity and linear acceleration and dividing it by _gravity
// Unit: g's
double IMUSensor::getVertAccel()
{
  return vertAccel;
}

// Places the calibration values in the calib variable, ranges from 0 to 3,
// the higher the better
int * IMUSensor::getCalibration()
{
  return calib;
}

imu::Vector<3> IMUSensor::getEuler()
{
  return euler;
}
