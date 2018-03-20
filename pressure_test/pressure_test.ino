#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPL115A2.h>

Adafruit_MPL115A2 mpl115a2;

float time_delta = .1; //time in seconds

float calc_altitude(float pressure, float temp)
{
  float Po = 1013.25; //Sea Level Pressure (hPa)
  float alt = 0.0;
  float altbetter = 0.0;

  pressure = pressure * 10.0; //Convert to hPa
    
  alt = ((pow(Po/pressure,1/5.257)-1)*(temp+273.15))/(0.0065);
  
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
    unsigned short i = 0, iterations = 20;
    float pressureKPA = 0, temperatureC = 0, sum_pressureKPA = 0, sum_temperatureC = 0, avg_pressureKPA = 0, avg_temperatureC = 0, altitude = 0.0;

    for (i = 0; i < iterations; i++) {
       mpl115a2.getPT(&pressureKPA, &temperatureC);
       sum_pressureKPA += pressureKPA;
       sum_temperatureC += temperatureC;
    }

    avg_pressureKPA = sum_pressureKPA / iterations;
    avg_temperatureC = sum_temperatureC / iterations;
    
    altitude = calc_altitude(avg_pressureKPA, avg_temperatureC);

    Serial.print("Pressure (kPa): "); Serial.print(pressureKPA, 4); Serial.print(" kPa  ");
    Serial.println("Temp (*C): "); Serial.print(temperatureC, 1); Serial.println(" *C both measured together");    
    Serial.print("Altitude:"); Serial.print(altitude, 1); Serial.println(" meters");

  }
  else {
    Serial.println("Setup never ran, trying to run again");
    delay(1000);
    setup();
  }
  delay(time_delta * 1000);
}



