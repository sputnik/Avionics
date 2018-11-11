#include "RTCSensor.h"

RTCSensor::RTCSensor()
{
  mill = new RTC_Millis();
  diff = mill->now();
}
