#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>      //AMU 9-Axis orientation sensor & accelerometer
#include <utility/imumaths.h>
#include <Adafruit_MPL115A2.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// The TinyGPS++ Object
//TinyGPSPlus gps;

// The MP115A2  Object
Adafruit_MPL115A2 mpl115a2;

/****************************************************
 * All variable are global and are in the 
 * variable_definitions file
 ***************************************************/
 
void setup(void)
{
  Serial.begin(9600);
  Serial.print("Launching Board...");

  //ss.begin(GPSBaud);
  //Serial.print("GPS Software Serial Started...");
  
  mpl115a2.begin();
  Serial.print("MP1115A2 Initialized...");

  //Setup More Stuff here

  Serial.println("Setup Finished");
  
}

void loop() {
    
    //While on the Launch Pad
    while (current_status == 0) {
      current_status = get_current_status();
      while_on_pad();
    }

    //During Engine Burn
    while (current_status == 1) {
      current_status = get_current_status();
      while_launching();
    }

    //During Upward Travel Engine Burned Out
    while (current_status = 2) {
      current_status = get_current_status();
      while_still_rising();
    }

    //During Descent
    while (current_status = 3) {
      while_descending();
    }
}
