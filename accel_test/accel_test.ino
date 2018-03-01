#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>      //AMU 9-Axis orientation sensor & accelerometer
#include <utility/imumaths.h>


float time_delta = .50;


void print_BNO_data();
void print_adxl_data();
#define BNO055_SAMPLERATE_DELAY_MS (time_delta * 1000)

float height = 0;
float velocity = 0;
float yAccel = 0;
float lheight = 0;
float lvelocity = 0;

Adafruit_BNO055 bno = Adafruit_BNO055();

bool setuprun = false;


void setup() {
  delay(1000);
  Serial.begin(9600);    // default NMEA GPS baud
  delay(1000);

  Serial.println("MCP9808 demo");
  delay(500);
  Serial.println("It's working!");
  setuprun = true;



  Serial.println("Still working, Not stuck");

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
  Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");

  //ADXL377
  Serial.println("ADXL Connected!");
}



void loop() {
  if (setuprun == true) {

    /* Display the floating point data */
    /*pseudo code
     * if(vertical_accel < 2G && > -2G) {
     *  then find altitude from accelerometer
     *  --this entails using euler angles to find
     *  }
     *  else {
     *  do nothing
     *  }
     *  
     * 
     */
    print_ADXL_data();
    print_BNO_data();

}

void print_ADXL_data() {
  Serial.print("\nADXL377: \t");
  int ADXL377_X_axis = analogRead(A0);
  int ADXL377_Y_axis = analogRead(A1);
  int ADXL377_Z_axis = analogRead(A2);
  Serial.println("RAW DATA");
  Serial.print("X Axis: "); Serial.print(ADXL377_X_axis);
  Serial.print("\t Y Axis: "); Serial.print(ADXL377_Y_axis);
  Serial.print("\t Z Axis: "); Serial.println(ADXL377_Z_axis);

  // Convert raw values to 'milli-Gs"
  long xScaled = map(ADXL377_X_axis, 512, 517, -1000, 1000);
  long yScaled = map(ADXL377_Y_axis, 512, 517, -1000, 1000);
  long zScaled = map(ADXL377_Z_axis, 511, 517, -1000, 1000);

  // re-scale to fractional Gs
  float xAccel = xScaled / 1000.0;
  float yAccel = yScaled / 1000.0;
  float zAccel = zScaled / 1000.0;

  height = height + (velocity * time_delta) + (.5 * yAccel * 9.81 * time_delta * time_delta);
  velocity = velocity + (yAccel * 9.81 * time_delta);

  Serial.print(" :: ");
  Serial.print(xAccel);
  Serial.print("G, ");
  Serial.print(yAccel);
  Serial.print("G, ");
  Serial.print(zAccel);
  Serial.println("G");
  Serial.print("Height:, ");
  Serial.print(height);
  Serial.print("Velocity:, ");
  Serial.println(velocity);
}

