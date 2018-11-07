#ifndef GPSSENSOR_H_
#define GPSSENSOR_H_

#include <TinyGPS++.h>

class GPSSensor
{
  public:
    GPSSensor();

    inline double getLat()
    {
      return gps->lat();
    }

    inline double getLong()
    {
      return gps->lng();
    }

    inline boolean connected()
    {
      return gps->isValid();
    }

  private:
    TinyGPSPlus * gps;
};
#endif
