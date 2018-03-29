#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>      //AMU 9-Axis orientation sensor & accelerometer
#include <utility/imumaths.h>
#include <Adafruit_MPL115A2.h>
#include <Adafruit_GPS.h>
#include <SD.h>
#include "RTClib.h"
 
File myFile;

RTC_DS3231 rtc;
Adafruit_MPL115A2 mpl115a2;

  float time_delta = .50;
  float height = 0;
  float velocity = 0;
  float yAccel = 0;
  float lheight = 0;
  float lvelocity = 0;
  float verticalAccel = 0;
  float ADXL_accel[3];
  float BNO_accel[3];
  float pressure = 0;
  
  char SD_data[400];
  char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  
  bool launchvalue = false;

  #define BNO055_SAMPLERATE_DELAY_MS (time_delta * 1000)
  #define GPSSerial Serial1
  #define GPSECHO true

Adafruit_BNO055 bno = Adafruit_BNO055();
Adafruit_GPS GPS(&GPSSerial);

void get_ADXL_data(float accel_vals[]);
float get_BNO_change_height();
float calc_altitude(float pressure, float temp);

void setup(void) 
{
  
  Serial.begin(9600);
  Serial.print("Initializing systems...");
  
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
   pinMode(10, OUTPUT);
 
  if (!SD.begin(10)) {
    Serial.println("SD card initialization failed! Check connections and/or insert a valid microSD card");
    return;
  }
  
  Serial.println("SD Card initialization successful.");
    
  mpl115a2.begin();

  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
  }
  else {
    Serial.println("BNO initialization successful.");
    if (bno.isFullyCalibrated()) {
      Serial.println("BNO Fully Calibrated!");
    }
    else {
      Serial.println("BNO NOT Calibrated");
    }
  }

  bno.setExtCrystalUse(true);
  mpl115a2.begin();

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  else {
    Serial.println("RTC initialization successful.");
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  
}



void loop() {
  get_ADXL_data(ADXL_accel);

  sprintf(SD_data, "The height is: %lf\n
                    The velocity is: %lf\n
                    The acceleration is: %lf\n
                    The pressure is: %lf\n
                    The time is: %d:%d:%d\n
                    The date is: %d/%d/%d\n", height, velocity, verticalAccel, );

}

void write_to_SD(char SD_info[]) {
  
  Serial.print("Writing data to SD...");
  rocket_data = SD.open("rocket_data.txt",FILE_WRITE);
  rocket_data.println(SD_info);
  rocket_data.close();
  Serial.println("DONE!");
  
}

float get_BNO_change_height() {

    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    imu::Vector<3> acc = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    imu::Vector<3> linear = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
    imu::Vector<3> gravity = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
 
    verticalAccel = ((linear.x() * gravity.x()) + (linear.y() * gravity.y()) + (linear.z() * gravity.z())) / (-9.81);
    if (verticalAccel >= .5) {
      launchvalue = true ;
    }
    if (verticalAccel <= -.5) {
      launchvalue = true ;
    }
    if (launchvalue = false); {
      verticalAccel = 0;
    }
    lheight = lheight + (lvelocity * time_delta) + (.5 * verticalAccel * time_delta * time_delta);
    lvelocity = lvelocity + (verticalAccel * time_delta);

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

float calc_altitude(float pressure, float temp) 
{
  float Po = 1013.25; //Sea Level Pressure (hPa)
  float alt = 0.0;

  pressure = pressure / 10.0; //Convert to hPa

  alt = ((pow(Po/pressure,1/5.257)-1)*(temp+273.15))/(0.0065);

  return alt;
}
