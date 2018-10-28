#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_BNO055.h"
#include "utility/imumaths.h"
#include "IMUSensor.h"

IMUSensor(int pinUsed, uint8_t address)
{
  _bno = Adafruit_BNO055(pinUsed, address);
}

// Updates the data from the imu
void updateData()
{
  _euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER); // Unit: degrees
  _gravity = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY); // Unit: m/s/s
  _acc = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER); // Unit: m/s/s
  _linear = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL); // Unit: m/s/s
}

// Calculates the vertical acceleration by taking the dot product of the
// gravity and linear acceleration and dividing it by _gravity
// Unit: g's
double calculateVertAccel()
{
  _vertAccel = (gravity[0]*linear[0] + gravity[1]*linear[1] + gravity[2]*linear[2])/9.81;
}

// Places the calibration values in the calib variable, ranges from 0 to 3,
// the higher the better
void getCalibration()
{
  uint8_t system, gyro, accel, mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);
  _calib[0] = system;
  _calib[1] = gyro;
  _calib[2] = accel;
  _calib[3] = mag;
}
