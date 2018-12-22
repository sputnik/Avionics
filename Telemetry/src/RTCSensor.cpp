// Class file for RTC sensor
#include "RTCSensor.h"

// Construct the sensor object
RTCSensor::RTCSensor()
{
  rtc = new RTC_DS3231();
  start = rtc->now(); // Sets the initial time
} // end constructor

// Destruction
RTCSensor::~RTCSensor()
{
  delete rtc;
} // end Destruction
