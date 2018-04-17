#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>      //AMU 9-Axis orientation sensor & accelerometer
#include <utility/imumaths.h>
#include <Adafruit_MPL115A2.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// The TinyGPS++ Object
TinyGPSPlus gps;

// The MP115A2  Object
Adafruit_MPL115A2 mpl115a2;

/****************************************************
 * All variable are global and are in the 
 * variable_definitions file
 ***************************************************/

/****************************************************
 * this function (gets), 
 * calculates (math), 
 * and puts the results in (variables)
 * 
 * INPUTS(global/internal(passed in)): 
 * OUTPUTS(global/internal(returned)): 
 ***************************************************/

 
void setup(void)
{
  Serial.begin(9600);
  Serial.print("Launching Board...");

  ss.begin(GPSBaud);
  Serial.print("GPS Software Serial Started...");
  
  mpl115a2.begin();
  Serial.print("MP1115A2 Initialized...");

  Serial.println("Setup Finished");
  
}

void loop() {

    //current_status is 0 if on the launchpad, 1 if  accellerating up, 2 if still going up but acceleration reducing, and 3 if descending
    
    //While on the Launch Pad
    while (current_status == 0) {
      current_status = get_current_status();
      get_GPS_data();
      
      //calculate vertical acceleration and set it to zero if it is negligible
      //send gps coordinates and radio pings so the rocket can be located in case of total software failure
    }

    //During Engine Burn
    while (current_status == 1) {
      current_status = get_current_status();
      check_airbrakes();
      
      /*calculate vertical acceleration, and calculate height and velocity from vertical acceleration
      calculate height from the barometer
      calculate averaged height and averaged velocity from the barometer and accererometer values, and use these values for the next iteration of calculations
      send gps coordinates and radio pings so the rocket can be located in case of total software failure
      */
    }

    //During Upward Travel Engine Burned Out
    while (current_status = 2) {
      current_status = get_current_status();
      
      //calculate vertical acceleration, and calculate height and velocity from vertical acceleration
      //calculate height from the barometer
      //calculate averaged height and averaged velocity from the barometer and accererometer values, and use these values for the next iteration of calculations
      //send gps coordinates and radio pings so the rocket can be located in case of total software failure
      //compare current height and velocity to pre generated height/velocity curve to determine if the rocket should be braking
      //make sure to save the vaules for how far open the airbrakes are at any given time, along with the height, velocity, and acceleration values
      //check the weird bolts to make sure that the airbrakes are not broken
      //CONSIDER ADDING SOMETHING TO MAKE SURE THE AIRBRAKES OPEN AT LEAST ONCE IN ORDER TO GATHER DATA IN CASE OF REALLY LOW FLIGHT
    }

    //During Descent
    while (current_status = 3) {
      //Blah
    }
}

int get_current_status() {
  get_
}

