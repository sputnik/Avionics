#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>      //AMU 9-Axis orientation sensor & accelerometer
#include <utility/imumaths.h>
#include <Adafruit_MPL115A2.h>

Adafruit_MPL115A2 mpl115a2;

float time_delta = .1;


void print_BNO_data();
void print_adxl_data();
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

#define BNO055_SAMPLERATE_DELAY_MS (time_delta * 1000)

float height = 0;
float velocity = 0;
float yAccel = 0;
float lheight = 0;
float lvelocity = 0;
float verticalAccel = 0;
float verticalAccelADXL = 0;
float lheightADXL = 0;
float lvelocityADXL = 0;
bool launchvalue = false;
float time1;
float time2;
float timedelta;
float waittime;
float time3;
float looptime;


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

  Serial.println("Getting barometric pressure ...");
  mpl115a2.begin();
}



void loop() {
  if (setuprun == true) {
    time1 = micros();
    /* Display the floating point data */
    /*pseudo code
       if(vertical_accel < 2G && > -2G) {
        then find altitude from accelerometer
        --this entails using euler angles to find
        }
        else {
        do nothing
        }
    */

    //get all values from accelerometer
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    imu::Vector<3> acc = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    imu::Vector<3> linear = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
    imu::Vector<3> gravity = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
    int ADXL377_X_axis = analogRead(A0);
    int ADXL377_Y_axis = analogRead(A1);
    int ADXL377_Z_axis = analogRead(A2);

    // Convert raw values to 'milli-Gs"
    long xScaled = map(ADXL377_X_axis, 512, 537, -1000, 1000);
    long yScaled = map(ADXL377_Y_axis, 512, 539, -1000, 1000);
    long zScaled = map(ADXL377_Z_axis, 512, 537, -1000, 1000);

    // re-scale to fractional Gs
    float xAccel = xScaled / 1000.0;
    float yAccel = yScaled / 1000.0;
    float zAccel = zScaled / 1000.0;

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

    verticalAccel = ((linear.x() * gravity.x()) + (linear.y() * gravity.y()) + (linear.z() * gravity.z())) / (9.81);
    if (verticalAccel >= .5) {
      launchvalue = true ;
      Serial.println(verticalAccel);
    }
    if (verticalAccel <= -.5) {
      launchvalue = true ;
      Serial.println(verticalAccel);
    }
    if (launchvalue == true) {
      Serial.print("WE HAVE LAUNCHED:, ");
    }
    if (launchvalue == false) {
      verticalAccel = 0;
    }
    else {
      Serial.print("THIS NUMBER SHOULD NOT BE ZERO. EVER");
      Serial.println(verticalAccel);
    }
    lheight = lheight + (lvelocity * time_delta) + (.5 * verticalAccel * time_delta * time_delta);
    lvelocity = lvelocity + (verticalAccel * time_delta);
    float part1 = (acc.x() * acc.x()) + (acc.y() * acc.y()) + (acc.z() * acc.z());
    float part2 = (xAccel * xAccel) + (yAccel * yAccel) + (zAccel * zAccel);
    if (launchvalue == true) {
      verticalAccelADXL = verticalAccel * 9.81 * sqrt((xAccel * xAccel) + (yAccel * yAccel) + (zAccel * zAccel)) / sqrt((acc.x() * acc.x()) + (acc.y() * acc.y()) + (acc.z() * acc.z()));
   // verticalAccelADXL = verticalAccel * 9.81 * sqrt((xAccel * xAccel) + (yAccel * yAccel) + (zAccel * zAccel)) / sqrt((acc.x() * acc.x()) + (acc.y() * acc.y()) + (acc.z() * acc.z()));
      lheightADXL = lheightADXL + (lvelocityADXL * time_delta) + (.5 * verticalAccelADXL * time_delta * time_delta);
      lvelocityADXL = lvelocityADXL + (verticalAccelADXL * time_delta);
    }
    Serial.print("LHeight:, ");
    Serial.println(lheight);
    Serial.print("LVelocity:, ");
    Serial.println(lvelocity);
    Serial.print("VerticalAccel:, ");
    Serial.println(verticalAccel);
    Serial.print("LHeight from ADXL:, ");
    Serial.println(lheightADXL);
    Serial.print("LVelocity from ADXL:, ");
    Serial.println(lvelocityADXL);
    Serial.print("VerticalAccel from ADXL:, ");
    Serial.println(verticalAccelADXL);
    Serial.print("part1:, ");
    Serial.println(part1);
    Serial.print("part2:, ");
    Serial.println(part2);
    Serial.println("--------");

    Serial.print("\t\tGravity: ");
    Serial.print("X: ");
    Serial.print(gravity.x());
    Serial.print(" Y: ");
    Serial.print(gravity.y());
    Serial.print(" Z: ");
    Serial.print(gravity.z());
    Serial.println("\t\t");

    Serial.print("\t\tHARDWARE Linear Acceleration: ");
    Serial.print("X: ");
    Serial.print(linear.x());
    Serial.print(" Y: ");
    Serial.print(linear.y());
    Serial.print(" Z: ");
    Serial.print(linear.z());
    Serial.println("\t\t");

    Serial.print("\t\tESTIMATED Linear Acceleration: ");
    Serial.print("X: ");
    Serial.print(acc.x() - gravity.x());
    Serial.print(" Y: ");
    Serial.print(acc.y() - gravity.y());
    Serial.print(" Z: ");
    Serial.print(acc.z() - gravity.z());
    Serial.println("\t\t");

    Serial.print("\t\tComparing BNO to ADXL: ");
    Serial.print("X: ");
    Serial.print(acc.x() / 9.81);
    Serial.print(" Y: ");
    Serial.print(acc.y() / 9.81);
    Serial.print(" Z: ");
    Serial.print(acc.z() / 9.81);
    Serial.print("\t\tADXL");
    Serial.print("X: ");
    Serial.print(xAccel);
    Serial.print(" Y: ");
    Serial.print(yAccel);
    Serial.print(" Z: ");
    Serial.print(zAccel);
    Serial.println("\t\t");


    Serial.println("====================");


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
    // print_ADXL_data();
    //print_BNO_data();

  }
  else {
    Serial.println("Setup never ran, trying to run again");
    delay(1000);
    setup();
  }
  time2 = micros();
  timedelta = (time2 - time1) / 1000000;
  waittime = time_delta - timedelta;
  delay(waittime * 1000);
  time3 = micros();
  looptime = (time3 - time1)/1000000;
  Serial.print(" timedelta: ");
  Serial.println(timedelta);
  Serial.print(" timedelta assumed: ");
  Serial.println(time_delta);
  Serial.print(" loop time: ");
  Serial.println(looptime);
}

void print_BNO_data() {

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
  //  height = height + (velocity * time_delta) + (.5 * vertical_accel * 9.81 * time_delta * time_delta);
  //velocity = velocity + (vertical _accel * 9.81 * time_delta);

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
  Serial.println("\n");
}

