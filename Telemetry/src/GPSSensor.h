// Class file for the gps sensor

#ifndef GPSSENSOR_H_
#define GPSSENSOR_H_

#include <TinyGPS++.h>
//#include <string>

class GPSSensor
{
  public:
    // Constructs the sensor
    GPSSensor();

    // Returns the current latitude
    inline double lat()
    {
      return gps->location.lat();
    }

    // Returns the current longitude
    inline double lng()
    {
      return gps->location.lng();
    }

    // Returns whether or not the gps is connected to a satellite
    inline boolean connected()
    {
      return gps->satellites.isValid();
    }

    // Returns the speed in mph
    inline double speed()
    {
      return gps->speed.mph();
    }

    // Returns the altitude in feet
    inline double alt()
    {
      return gps->altitude.feet();
    }

    // Returns the date for naming SD card files
    String date();

    // Returns the date and time for writing in the file
    String dateAndTime();

    // Destroys the sensor
    ~GPSSensor();

  private:
    // Pointer to the gps sensor
    TinyGPSPlus * gps;
};
#endif
