#include <Wire.h>
#include <Adafruit_MPL115A2.h>

Adafruit_MPL115A2 mpl115a2;

float calc_altitude(float pressure, float temp) 
{
  float Po = 1013.25; //Sea Level Pressure (hPa)
  float alt = 0.0;

  pressure = pressure / 10.0; //Convert to hPa

  alt = ((pow(Po/pressure,1/5.257)-1)*(temp+273.15))/(0.0065);

  return alt;
}

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Hello!");
  
  Serial.println("Getting barometric pressure ...");
  mpl115a2.begin();
}

void loop(void) 
{
  float pressureKPA = 0, temperatureC = 0, altitude = 0.0;  

  mpl115a2.getPT(&pressureKPA,&temperatureC);
  Serial.print("Pressure (kPa): "); Serial.print(pressureKPA, 4); Serial.print(" kPa  ");
  Serial.print("Temp (*C): "); Serial.print(temperatureC, 1); Serial.println(" *C both measured together");
  
  pressureKPA = mpl115a2.getPressure();  
  Serial.print("Pressure (kPa): "); Serial.print(pressureKPA, 4); Serial.println(" kPa");

  temperatureC = mpl115a2.getTemperature();  
  Serial.print("Temp (*C): "); Serial.print(temperatureC, 1); Serial.println(" *C");

  altitude = calc_altitude(pressureKPA, temperatureC);
  Serial.print("Altitude:"); Serial.print(altitude, 1); Serial.println(" meters");
  
  delay(1000);
}

