#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>      //AMU 9-Axis orientation sensor & accelerometer
#include <utility/imumaths.h>
#include <Adafruit_MPL115A2.h>

Adafruit_MPL115A2 mpl115a2;

float time_delta = .50;
float height = 0;
float velocity = 0;
float yAccel = 0;
float lheight = 0;
float lvelocity = 0;
float verticalAccel = 0;

bool launchvalue = false;

#define BNO055_SAMPLERATE_DELAY_MS (time_delta * 1000)

Adafruit_BNO055 bno = Adafruit_BNO055();

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
  
  float acceleration[3];
  mpl115a2.begin();
  
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
  }
  else {
    Serial.println("BNO Connected!");
    if (bno.isFullyCalibrated()) {
      Serial.println("BNO Fully Calibrated!");
    }
    else {
      Serial.println("BNO NOT Calibrated");
    }
  }

  bno.setExtCrystalUse(true);
  mpl115a2.begin();
}

void get__BNO_data() {

}

void get_ADXL_data(accel_vals[]) {
  int ADXL377_X_axis = analogRead(A0);
  int ADXL377_Y_axis = analogRead(A1);
  int ADXL377_Z_axis = analogRead(A2);

  // Convert raw values to 'milli-Gs"
  long xScaled = map(ADXL377_X_axis, 512, 517, -1000, 1000);
  long yScaled = map(ADXL377_Y_axis, 512, 517, -1000, 1000);
  long zScaled = map(ADXL377_Z_axis, 511, 517, -1000, 1000);

  // re-scale to fractional Gs
  float xAccel = xScaled / 1000.0;
  float yAccel = yScaled / 1000.0;
  float zAccel = zScaled / 1000.0;

  // convert linear value and euler angles to purely vertical accel
  // float vertical_accel = xAccel * sin( invcos( (sqrt( (xAccel * cos( euler.x ))^2 + (xAccel * cos( euler.y ))^2)/ xAccel)));
  // height = height + (velocity * time_delta) + (.5 * vertical_accel * 9.81 * time_delta * time_delta);
  // velocity = velocity + (vertical _accel * 9.81 * time_delta);

  accel_vals[0] = xAccel;
  accel_vals[1] = yAccel;
  accel_vals[2] = zAccel;

}

void loop() {
  get_ADXL_data(acceleration);

}
