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
  else {
    Serial.println("Setup never ran, trying to run again");
    delay(1000);
    setup();
  }
  delay(time_delta * 1000);
}

void print_BNO_data() {
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  imu::Vector<3> acc = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  imu::Vector<3> linear = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  Serial.print("BNO055: \t");
  Serial.print("Euler angles: ");
  Serial.print("X: ");
  Serial.print(euler.x());
  Serial.print(" Y: ");
  Serial.print(euler.y());
  Serial.print(" Z: ");
  Serial.print(euler.z());
  Serial.print("\t\t");
  /* Display calibration status for each sensor. */
  uint8_t system, gyro, accel, mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);
  Serial.print("CALIBRATION: Sys=");
  Serial.print(system, DEC);
  Serial.print(" Gyro=");
  Serial.print(gyro, DEC);
  Serial.print(" Accel=");
  Serial.print(accel, DEC);
  Serial.print(" Mag=");
  Serial.println(mag, DEC);

  Serial.print("\t\tAcceleration: ");
  Serial.print("X: ");
  Serial.print(acc.x());
  Serial.print(" Y: ");
  Serial.print(acc.y());
  Serial.print(" Z: ");
  Serial.print(acc.z());
  Serial.println("\t\t");

  Serial.print("\t\tLinear Acceleration: ");
  Serial.print("X: ");
  Serial.print(linear.x());
  Serial.print(" Y: ");
  Serial.print(linear.y());
  Serial.print(" Z: ");
  Serial.print(linear.z());
  Serial.println("\t\t");
  lheight = lheight + (lvelocity * time_delta) + (.5 * linear.z() * 9.81 * time_delta * time_delta);
  lvelocity = lvelocity + (linear.z() * 9.81 * time_delta);
  Serial.print("LHeight:, ");
  Serial.print(lheight);
  Serial.print("LVelocity:, ");
  Serial.println(lvelocity);
  Serial.println("--------");


  Serial.println("====================");
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

  // onvert linear value and euler angles to purely vertical accel
  // float vertical_accel = xAccel * sin( invcos( (sqrt( (xAccel * cos( euler.x ))^2 + (xAccel * cos( euler.y ))^2)/ xAccel)));
  height = height + (velocity * time_delta) + (.5 * vertical_accel * 9.81 * time_delta * time_delta);
  velocity = velocity + (vertical _accel * 9.81 * time_delta);

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

