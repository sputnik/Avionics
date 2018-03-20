#include <Wire.h>
#include <Adafruit_Sensor.h>
//#include <utility/imumaths.h>
#include <Adafruit_MPL115A2.h>

Adafruit_MPL115A2 mpl115a2;

float time_delta = .50; //time in seconds

float calc_altitude(float pressure, float temp)
{
  float Po = 1013.25; //Sea Level Pressure (hPa)
  float alt = 0.0;

  pressure = pressure / 10.0; //Convert to hPa

  alt = (1 - (pow((pressure / Po), (1 / 5.257)))) * 44330;

  Serial.print("\n\nPressure Data: ");
  Serial.print("P0: ");
  Serial.print(Po);
  Serial.print(" MPL115A2: ");
  Serial.print(pressure);
  Serial.print(" Altitude: ");
  Serial.print(alt);
  Serial.print("\t\t\n");
  return alt;
}


float height = 0;
float velocity = 0;
float yAccel = 0;
float lheight = 0;
float lvelocity = 0;

bool setuprun = false;


void setup() {
  delay(1000);
  Serial.begin(9600);    // default NMEA GPS baud
  delay(1000);

  Serial.println("MCP9808 demo");
  delay(500);
  Serial.println("It's working!");
  setuprun = true;

  Serial.println("Getting barometric pressure ...");
  mpl115a2.begin();
}



void loop() {
  if (setuprun == true) {
    float pressureKPA = 0, temperatureC = 0, altitude = 0.0;

    mpl115a2.getPT(&pressureKPA, &temperatureC);
    Serial.print("Pressure (kPa): "); Serial.print(pressureKPA, 4); Serial.print(" kPa  ");
    Serial.print("Temp (*C): "); Serial.print(temperatureC, 1); Serial.println(" *C both measured together");

    pressureKPA = mpl115a2.getPressure();
    Serial.print("Pressure (kPa): "); Serial.print(pressureKPA, 4); Serial.println(" kPa");

    temperatureC = mpl115a2.getTemperature();
    Serial.print("Temp (*C): "); Serial.print(temperatureC, 1); Serial.println(" *C");

    altitude = calc_altitude(pressureKPA, temperatureC);
    Serial.print("Altitude:"); Serial.print(altitude, 1); Serial.println(" meters");

  }
  else {
    Serial.println("Setup never ran, trying to run again");
    delay(1000);
    setup();
  }
  delay(time_delta * 1000);
}



