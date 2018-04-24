#include <Wire.h>
#include <math.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>      //AMU 9-Axis orientation sensor & accelerometer
#include <utility/imumaths.h>
#include <Adafruit_MPL115A2.h>
//#include <TinyGPS++.h>
#include <SD.h>
#include "RTClib.h"
#include "VariableDefinitions.h"

//function declarations
void check_airbrakes();
void get_Alt_BNO();
void get_Avg_Alt();
void write_to_SD(char SD_info[]);
void while_on_pad();
void while_launching();
void while_still_rising();
void while_descending();
void get_Time(void);
int get_current_status(void);
float get_Alt_Pressure();

// The TinyGPS++ Object
//TinyGPSPlus gps;

// The MP115A2  Object
Adafruit_MPL115A2 mpl115a2;

// The RTC DS3231 Object
RTC_DS3231 rtc;

/****************************************************
   All variable are global and are in the
   variable_definitions file
 ***************************************************/

//Variable to make sure setup ran
bool SetupRun = false;

//Accelerometer
Adafruit_BNO055 bno = Adafruit_BNO055();

void setup(void)
{
  SetupRun = true;
  Serial.begin(9600);
  
  //SD Card
  pinMode(SDCS_pin, OUTPUT);
  if (!SD.begin(SDCS_pin)) {
    Serial.println("SD card initialization failed! Check connections and/or insert a valid microSD card");
  }
  else {
    Serial.println("SD Card initialization successful.");
  }
  
  sprintf(SD_data, "Launching Board...\n");
  write_to_SD(SD_data);
  //Serial.print("Launching Board...");

  //ss.begin(GPSBaud);
  //Serial.print("GPS Software Serial Started...");

  // Initialize RTC
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  else {
    Serial.println("RTC initialization successful.");
  }
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  mpl115a2.begin();
    sprintf(SD_data, "MPL115A2 Initialized...\n");
  write_to_SD(SD_data);
  //Serial.print("MP1115A2 Initialized...");

  //Setup More Stuff here
  sprintf(SD_data, "Setup Finished!\n");
  write_to_SD(SD_data);
  //Serial.println("Setup Finished");
}

void loop() {
  if (SetupRun) {

    //While on the Launch Pad
    while (current_status == 0) {
      current_status = get_current_status();
      while_on_pad();
      get_Time();
      sprintf(SD_data, "The height is: %lf\nThe velocity is: %lf\nThe acceleration is: %lf\nThe pressure is: %lf\nThe time is: %d:%d:%d\nThe date is: %d/%d/%d\n\n\n", AvgHeight, AvgVelocity, VerticalAccelBNO, pressure, rtc_time[0], rtc_time[1], rtc_time[2], rtc_time[3], rtc_time[4], rtc_time[5]);
      write_to_SD(SD_data);
    }

    //During Engine Burn
    while (current_status == 1) {
      current_status = get_current_status();
      while_launching();
      get_Time();
      sprintf(SD_data, "The height is: %lf\nThe velocity is: %lf\nThe acceleration is: %lf\nThe pressure is: %lf\nThe time is: %d:%d:%d\nThe date is: %d/%d/%d\n\n\n", AvgHeight, AvgVelocity, VerticalAccelBNO, pressure, rtc_time[0], rtc_time[1], rtc_time[2], rtc_time[3], rtc_time[4], rtc_time[5]);
      write_to_SD(SD_data);
    }

    //During Upward Travel Engine Burned Out
    while (current_status == 2) {
      current_status = get_current_status();
      while_still_rising();
      get_Time();
      sprintf(SD_data, "The height is: %lf\nThe velocity is: %lf\nThe acceleration is: %lf\n The percent open is: %lf\nThe pressure is: %lf\nThe time is: %d:%d:%d\nThe date is: %d/%d/%d\n\n\n", AvgHeight, AvgVelocity, VerticalAccelBNO, PercentOpen, pressure, rtc_time[0], rtc_time[1], rtc_time[2], rtc_time[3], rtc_time[4], rtc_time[5]);
      write_to_SD(SD_data);
    }

    //During Descent
    while (current_status == 3) {
      while_descending();
      get_Time();
    }
  }
  else {
    Serial.println("Setup never ran, trying again");
    delay(100);
    setup();
  }
}
