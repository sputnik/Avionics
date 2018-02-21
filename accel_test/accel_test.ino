#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>      //AMU 9-Axis orientation sensor & accelerometer
#include <utility/imumaths.h>
#include "RTClib.h"               // Real-Time Clock

RTC_DS3231 rtc;

#define time_delta

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};



#define BNO055_SAMPLERATE_DELAY_MS (100)



Adafruit_BNO055 bno = Adafruit_BNO055();



void setup() {
  delay(1000);
  Serial.begin(9600);    // default NMEA GPS baud
  delay(1000);

  Serial.println("MCP9808 demo");
  delay(500);
  Serial.println("It's working!");

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  else {
    Serial.println("RTC Connected!");
  }

  //Serial.println("Not stuck");
//  if (rtc.lostPower()) {
//    Serial.println("RTC lost power, lets set the time!");
//    // following line sets the RTC to the date & time this sketch was compiled
//    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//    // This line sets the RTC with an explicit date & time, for example to set
//    // January 21, 2014 at 3am you would call:
//    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
//  }

//  Serial.println("Still working, Not stuck");
//  
//   if(!bno.begin())
//  {
//    /* There was a problem detecting the BNO055 ... check your connections */
//    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
//  }
//  else {
//    Serial.println("BNO Connected!");
//  }
//
//  bno.setExtCrystalUse(true);
//  Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");

   //ADXL377
   Serial.println("ADXL Connected!");
}



void loop() {
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

    Serial.print(" :: ");
    Serial.print(xAccel);
    Serial.print("G, ");
    Serial.print(yAccel);
    Serial.print("G, ");
    Serial.print(zAccel);
    Serial.println("G");

////RTC
//  DateTime now = rtc.now();
//   Serial.print("DS3231: \t");
//   Serial.print(now.year(), DEC);
//    Serial.print('/');
//    Serial.print(now.month(), DEC);
//    Serial.print('/');
//    Serial.print(now.day(), DEC);
//    Serial.print(" (");
//    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
//    Serial.print(") ");
//    Serial.print(now.hour(), DEC);
//    Serial.print(':');
//    Serial.print(now.minute(), DEC);
//    Serial.print(':');
//    Serial.print(now.second(), DEC);
//    Serial.println();
//
//    /* Display the floating point data */
//    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
//    imu::Vector<3> acc = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
//  Serial.print("BNO055: \t");
//  Serial.print("Euler angles: ");
//  Serial.print("X: "); 
//  Serial.print(euler.x());
//  Serial.print(" Y: ");
//  Serial.print(euler.y());
//  Serial.print(" Z: ");
//  Serial.print(euler.z());
//  Serial.print("\t\t");
//  /* Display calibration status for each sensor. */
//  uint8_t system, gyro, accel, mag = 0;
//  bno.getCalibration(&system, &gyro, &accel, &mag);
//  Serial.print("CALIBRATION: Sys=");
//  Serial.print(system, DEC);
//  Serial.print(" Gyro=");
//  Serial.print(gyro, DEC);
//  Serial.print(" Accel=");
//  Serial.print(accel, DEC);
//  Serial.print(" Mag=");
//  Serial.println(mag, DEC);
//  
//  Serial.print("\t\tAcceleration: ");
//  Serial.print("X: "); 
//  Serial.print(acc.x());
//  Serial.print(" Y: ");
//  Serial.print(acc.y());
//  Serial.print(" Z: ");
//  Serial.print(acc.z());
//  Serial.println("\t\t");
//  
//
//  Serial.println("--------");
//
//  //Serial.println("");
//
//  Serial.println("====================");



  delay(time_delta);

}
