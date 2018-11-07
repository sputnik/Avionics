#ifndef IMUSENSOR_H_
#define IMUSENSOR_H_
#include <Adafruit_BNO055.h>

class IMUSensor
{
  public:
    IMUSensor(int32_t pinUsed, uint8_t address); // Constructs the sensor object
    void updateData(); // Updates the data

    // Returns the vertical acceleration in g's
    inline double getVertAccel()
    {
      return vertAccel;
    } // End getVertAccel

    // Returns the calibration of the sensor
    inline int * getCalibration()
    {
      return calib;
    } // End getCalibration

    // Returns the current Euler angles in degrees
    inline imu::Vector<3> getEuler()
    {
      return euler;
    } // End getEuler

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
