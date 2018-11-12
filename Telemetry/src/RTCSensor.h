// Header file for rtc sensor

#ifndef RTCSENSOR_H_
#define RTCSENSOR_H_

#include <RTClib.h>

class RTCSensor
{
  public:
    // Constructor
    RTCSensor();

    // Returns how many seconds have elapsed since start-up
    inline uint8_t seconds()
    {
      return rtc->now().second() - start.second();
    }

    // Destructor
    ~RTCSensor();

  private:
    // Pointer to the rtc sensor
    RTC_DS3231 * rtc;

    // The date and time at startup
    DateTime start;

};
#endif
