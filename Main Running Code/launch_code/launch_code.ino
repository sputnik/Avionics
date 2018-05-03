#include <Wire.h>
#include <SPI.h>
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
void write_to_SD();
void while_on_pad();
void while_launching(); 
void while_still_rising();
void while_descending();
void get_Time(void);
void get_current_status();
void get_Alt_Pressure();

// The TinyGPS++ Object
//TinyGPSPlus gps;

// The MP115A2  Object
Adafruit_MPL115A2 mpl115a2;

// The RTC DS3231 Object
RTC_DS3231 rtc;

File myFile;
int i = 0;

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
  
//Start Setup 
  SetupRun = true;
  Serial.begin(9600);
  Serial.println("Starting Setup");
  
//SD Card
  Serial.print("Initializing SD card...");

  if (!SD.begin(SDCS_pin)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("rocket.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Starting Up");
    myFile.println("System Starting Up...");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

    pinMode(LA_FDBK, INPUT);
    pinMode(LA_DIR, OUTPUT);
    pinMode(LA_PWM, OUTPUT);
// Initialize RTC
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  else {
    Serial.println("RTC initialization successful.");
  }
  // This line sets the RTC with an explicit date & time, for example to set
  // April 24, 2018 at 10:37:00 A.M. you would call:
  //rtc.adjust(DateTime(2018, 4, 24, 10, 37, 0));

//MP1115A2
  mpl115a2.begin();  

//Setup More Stuff here

  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
  }
  Serial.println("Setup Finished, Starting Main Program Now...");

}

void loop() {
  if (SetupRun) {

    //While on the Launch Pad
    while (current_status == 0) {
      get_current_status();
      while_on_pad();
      get_Time();
      get_Alt_BNO();
      get_Alt_Pressure();
      get_Avg_Alt();
      
      curr_time = millis();
      if (curr_time > (old_time + 40)) {
        sprintf(SD_data, "The Current Data Values  (On Pad) are:\tHeight: S%06d\tVelocity: S%06d\tAcceleration: S%06d\tHeightPressure: S%06d\tHeightBNO: S%06d\tThe time is: %02d:%02d:%02d\tThe date is: %02d/%02d/%04d", (int)(1000 * AvgHeight), (int)(1000 * AvgVelocity), (int)(1000 * VerticalAccelBNO), (int)(HeightPress * 1000), (int)(1000* HeightBNO), rtc_time[0], rtc_time[1], rtc_time[2], rtc_time[3], rtc_time[4], rtc_time[5]);
        write_to_SD();
        old_time = millis();
      }
    }

    //During Engine Burn
    while (current_status == 1) {
      get_current_status();
      while_launching();
      get_Time();
      get_Alt_BNO();
      get_Alt_Pressure();
      get_Avg_Alt();
      
      curr_time = millis();
      if (curr_time > (old_time + 40)) {
        sprintf(SD_data, "The Current Data Values  (Launching) are:\tHeight: S%06d\tVelocity: S%06d\tAcceleration: S%06d\tHeightPressure: S%06d\tHeightBNO: S%06d\tThe time is: %02d:%02d:%02d\tThe date is: %02d/%02d/%04d", (int)(1000 * AvgHeight), (int)(1000 * AvgVelocity), (int)(1000 * VerticalAccelBNO), (int)(HeightPress * 1000), (int)(1000* HeightBNO), rtc_time[0], rtc_time[1], rtc_time[2], rtc_time[3], rtc_time[4], rtc_time[5]);
        write_to_SD();
        old_time = millis();
      }
    }

    //During Upward Travel Engine Burned Out
    while (current_status == 2) {
      get_current_status();
      while_still_rising();
      get_Time();
      get_Alt_BNO();
      get_Alt_Pressure();
      get_Avg_Alt();
      check_airbrakes();
      
      curr_time = millis();
      if (curr_time > (old_time + 40)) {
        sprintf(SD_data, "The Current Data Values  (Braking) are:\tHeight: S%06d\tVelocity: S%06d\tAcceleration: S%06d\tHeightPressure: S%06d\tHeightBNO: S%06d\tDirectionPin: %06d\tPWMPin: %06d\tFDBKpin: %06d\tThe time is: %02d:%02d:%02d\tThe date is: %02d/%02d/%04d",(int)(1000 * AvgHeight), (int)(1000 * AvgVelocity), (int)(1000 * VerticalAccelBNO), (int)(1000 * HeightPress), (int)(HeightBNO), (int)LAdir, (int)LApwm, (int)LAfdbk, rtc_time[0], rtc_time[1], rtc_time[2], rtc_time[3], rtc_time[4], rtc_time[5]);
        write_to_SD();
        old_time = millis();
      }
    }

    //During Descent
    while (current_status == 3) {
      while_descending();
      get_Time();

      curr_time = millis();
      if (curr_time > (old_time + 40)) {      
        sprintf(SD_data, "The Rocket is Descending. Currently the time is: %02d:%02d:%02d\tThe date is: %02d/%02d/%04d", rtc_time[0], rtc_time[1], rtc_time[2], rtc_time[3], rtc_time[4], rtc_time[5]);
        write_to_SD();
        old_time = millis();
      }
    }
  }
  else {
    Serial.println("Setup never ran, trying again");
    delay(100);
    setup();
  }
}
