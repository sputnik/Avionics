#ifndef RTCSENSOR_H_
#define RTCSENSOR_H_

#include <RTClib.h>

class RTCSensor
{
  public:
    RTCSensor();

    inline void update()
    {
      diff =  + diff;
    }

    inline uint8_t seconds()
    {
      return diff.second();
    }

  private:
    RTC_Millis * mill;
    DateTime diff;

};
#endif
