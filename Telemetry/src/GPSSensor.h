#ifndef GPSSENSOR_H_
#define GPSSENSOR_H_

#include <TinyGPS++.h>

class GPSSensor
{
  public:
    GPSSensor();

    inline double getLat()
    {
      return gps->location.lat();
    }

    inline double getLong()
    {
      return gps->location.lng();
    }

    inline boolean connected()
    {
      return gps->satellites.isValid();
    }

    inline double speed()
    {
      return gps->speed.mph();
    }

    inline double alt()
    {
      return gps->altitude.feet();
    }
  private:
    TinyGPSPlus * gps;
};
#endif
