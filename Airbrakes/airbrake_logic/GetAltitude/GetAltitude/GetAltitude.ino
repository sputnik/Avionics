#include <Wire.h>
#include <Adafruit_MPL115A2.h>

Adafruit_MPL115A2 mpl115a2;

void setup(void)
{
  Serial.begin(9600);
  mpl115a2.begin();
}

float GetAltitude(void)
{//Gets altitude from pressure and temperature
  float pressureKPA = 0, temperatureC = 0;
  float P0 = 1013.25; //sea level pressure in kPa
  mpl115a2.getPT(&pressureKPA,&temperatureC);
  
  double x = P0 / pressureKPA;
  double y = 1 / 5.257;
  double power = pow(x, y);
  
  float h = ((power-1) * (temperatureC + 273.15)) / 0.0065;
  //equation is h=(((P0/P)^(1/5.257)-1)*(T+273.15))/0.0065
  return h;
}
