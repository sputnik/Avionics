#ifndef IMUSENSOR_H_
#define IMUSENSOR_H_
#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_BNO055.h"
#include "utility/imumaths.h"

class IMUSensor
{
  public:
    Adafruit_BNO055 bno;
    Adafruit_BNO055 *point = bno;
    point = NULL;

    imu::Vector<3> euler; // Euler angles in m/s/s
    imu::Vector<3> acc; // Acceleration in m/s/s
    imu::Vector<3> gravity; // Gravity in m/s/s
    imu::Vector<3> linear; // Linear acceleration in m/s/s
    int[4] calib; // Calibration values, 0 is bad, 3 is good

    double vertAccel; // Vertical Acceleration in g's

    IMUSensor(int pinUsed, uint8_t address); // Constructs the sensor object
    void updateData(); // Updates the data
    void calculateVertAccel(); // Calculates and returns the vertical accel
    void getCalibration(); // Gets the calibration of the sensor
};
#endif
