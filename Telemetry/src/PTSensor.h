// Class header for the pressure and temperature sensor

#ifndef PTSENSOR_H_
#define PTSENSOR_H_
#include <Adafruit_MPL115A2.h>

class PTSensor
{
  public:
    // Constructor
    PTSensor();

    // Returns the temperature in Celsius
    inline float getTemp()
    {
      return pt->getTemperature();
    }

    // Returns the pressure in kPa
    inline float getPress()
    {
      return pt->getPressure();
    }

    // THE DESTRUCTOR
    ~PTSensor();

  private:
    // Pointer to the sensor
    Adafruit_MPL115A2 * pt;
};
#endif
