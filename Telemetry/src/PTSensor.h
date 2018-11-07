#ifndef PTSENSOR_H_
#define PTSENSOR_H_
#include <Adafruit_MPL115A2.h>

class PTSensor
{
  public:
    PTSensor();

    inline float getTemp()
    {
      return pt->getTemperature();
    }

    inline float getPress()
    {
      return pt->getPressure();
    }

  private:
    Adafruit_MPL115A2 * pt;
};
#endif
