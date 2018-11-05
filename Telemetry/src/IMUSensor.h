#ifndef IMUSENSOR_H_
#define IMUSENSOR_H_
#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_BNO055.h"
#include "utility/imumaths.h"

class IMUSensor
{
  public:
    IMUSensor(int32_t pinUsed, uint8_t address); // Constructs the sensor object
    void updateData(); // Updates the data
    double getVertAccel(); // Returns the vertical acceleration
    int * getCalibration(); // Returns the calibration of the sensor
    imu::Vector<3> getEuler(); // Returns the current Euler angles

  private:
    Adafruit_BNO055 * bno;
    imu::Vector<3> euler; // Euler angles in m/s/s
    imu::Vector<3> acc; // Acceleration in m/s/s
    imu::Vector<3> gravity; // Gravity in m/s/s
    imu::Vector<3> linear; // Linear acceleration in m/s/s
    int calib[4]; // Calibration values, 0 is bad, 3 is good
    double vertAccel; // Vertical Acceleration in g's
};
#endif
