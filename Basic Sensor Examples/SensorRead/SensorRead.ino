#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "Adafruit_MCP9808.h"
#include <Adafruit_MPL115A2.h>
#include <Adafruit_GPS.h>
#include "RTClib.h"

Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
Adafruit_MPL115A2 mpl115a2;
RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055();
Adafruit_GPS GPS(&Serial1);

void setup() {
  Serial.begin(9600);
  //Serial1.begin(9600);      // default NMEA GPS baud
  GPS.begin(9600);
  Serial.println("MCP9808 demo");

  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);

  if (!tempsensor.begin()) {
    Serial.println("Couldn't find MCP9808!");
  }
  mpl115a2.begin();

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

   if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
  }
  bno.setExtCrystalUse(true);
  Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");
  
}

void loop() {
   //ADXL377
   int ADXL377_X_axis = analogRead(A0);
   int ADXL377_Y_axis = analogRead(A1);
   int ADXL377_Z_axis = analogRead(A2);
   Serial.print("ADXL377: \t");
   Serial.print("X Axis: "); Serial.print(ADXL377_X_axis);
   Serial.print("\t Y Axis: "); Serial.print(ADXL377_Y_axis);
   Serial.print("\t Z Axis: "); Serial.println(ADXL377_Z_axis);

  //MCP9808

  float c = tempsensor.readTempC();
  float f = c * 9.0 / 5.0 + 32;
  Serial.print("MCP9808: \t");
  Serial.print("Temp: "); Serial.print(c); Serial.print("*C\t"); 
  Serial.print(f); Serial.println("*F");

  //MPL115A2
  float pressureKPA = 0, temperatureC = 0;  
  mpl115a2.getPT(&pressureKPA,&temperatureC);
  Serial.print("MPL115A2: \t");
  Serial.print("Pressure (kPa): "); Serial.print(pressureKPA, 4); Serial.print(" kPa  ");
  Serial.print("Temp (*C): "); Serial.print(temperatureC, 1); Serial.println(" *C");

  DateTime now = rtc.now();
   Serial.print("DS3231: \t");
   Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    /* Display the floating point data */
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    imu::Vector<3> acc = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
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
  

  Serial.println("--------");
  char k = GPS.read();
  Serial.println(k);
  if (GPS.newNMEAreceived()) {
    Serial.print("\nTime: ");
    Serial.print(GPS.hour, DEC); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    Serial.println(GPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    if (GPS.fix) {
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", ");
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
    }
  }
  Serial.println("");
  Serial.println("====================");

  delay(1000);
}
