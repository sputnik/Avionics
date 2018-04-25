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
void get_Alt_Pressure();

// The TinyGPS++ Object
//TinyGPSPlus gps;

// The MP115A2  Object
Adafruit_MPL115A2 mpl115a2;

// The RTC DS3231 Object
RTC_DS3231 rtc;

File rocket_data;

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
  Serial.println("Starting Setup");
  
  //SD Card
  if (!SD.begin(SDCS_pin)) {
    Serial.println("SD card initialization failed! Check connections and/or insert a valid microSD card");
  }
  else {
    
    Serial.println("SD Card initialization successful.");
    if (! SD.exists("rocket_data.txt")) {
      
    }
    else {
      rocket_data = SD.open("rocket_data.txt", FILE_WRITE);
      if( ! rocket_data ) {
        Serial.print("Couldnt create "); 
        Serial.println("rocket_data.txt");
      }
      Serial.print("Writing to "); 
      Serial.println("rocket_data.txt"); 
    }
    pinMode(LA_FDBK, INPUT);
    pinMode(LA_DIR, OUTPUT);
    pinMode(LA_PWM, OUTPUT);
    
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
  // April 24, 2018 at 10:37am you would call:
  //rtc.adjust(DateTime(2018, 4, 24, 10, 37, 0));

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
      get_Alt_BNO();
      get_Alt_Pressure();
      get_Avg_Alt();
      sprintf(SD_data, "The height is: %d\nThe velocity is: %d\nThe acceleration is: %d\nThe pressure is: %d\nThe time is: %d:%d:%d\nThe date is: %d/%d/%d\n\n\n", (int)AvgHeight, (int)AvgVelocity, (int)VerticalAccelBNO, (int)HeightPress, rtc_time[0], rtc_time[1], rtc_time[2], rtc_time[3], rtc_time[4], rtc_time[5]);
      //Serial.println(SD_data);
      write_to_SD(SD_data);
    }

    //During Engine Burn
    while (current_status == 1) {
      current_status = get_current_status();
      while_launching();
      get_Time();
      get_Alt_BNO();
      get_Alt_Pressure();
      get_Avg_Alt();
      sprintf(SD_data, "The height is: %d\nThe velocity is: %d\nThe acceleration is: %d\nThe pressure is: %d\nThe time is: %d:%d:%d\nThe date is: %d/%d/%d\n\n\n", (int)AvgHeight, (int)AvgVelocity, (int)VerticalAccelBNO, (int)HeightPress, rtc_time[0], rtc_time[1], rtc_time[2], rtc_time[3], rtc_time[4], rtc_time[5]);
      write_to_SD(SD_data);
    }

    //During Upward Travel Engine Burned Out
    while (current_status == 2) {
      current_status = get_current_status();
      while_still_rising();
      get_Time();
      get_Alt_BNO();
      get_Alt_Pressure();
      get_Avg_Alt();
      check_airbrakes();
      sprintf(SD_data, "The height is: %d\nThe velocity is: %d\nThe acceleration is: %d\n The percent open is: %d\nThe pressure is: %d\nThe time is: %d:%d:%d\nThe date is: %d/%d/%d\n\n\n", (int)AvgHeight, (int)AvgVelocity, (int)VerticalAccelBNO, (int)PercentOpen, (int)HeightPress, rtc_time[0], rtc_time[1], rtc_time[2], rtc_time[3], rtc_time[4], rtc_time[5]);
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
