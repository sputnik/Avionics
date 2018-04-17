#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>      //AMU 9-Axis orientation sensor & accelerometer
#include <utility/imumaths.h>
#include <Adafruit_MPL115A2.h>

Adafruit_MPL115A2 mpl115a2;

float time_delta = .50; //time in seconds

/****************************************************
 * The following variables are made to
 * be accessible by any function and 
 * updated by any function starting 
 * with the word "update"
 ***************************************************/
float adxl_altitude;
float adxl_velocity;
float bno_altitude;
float bno_velocity;

//function prototypes
float alt_from_pressure(float pressure, float temp);
void update_altitude_from_ADXL(float accel_vals[]);
void update_altitude_from_BNO();

//--------Format for explaining what a function does------------------------------------------------------------------------
/*
 * this function (gets), 
 * calculates (math), 
 * and puts the results in (variables)
 * 
 * INPUTS(global/internal(passed in)): 
 * OUTPUTS(global/internal(returned)): 
 */

 
void setup(void)
{
  Serial.begin(9600);
  Serial.print("Launching Board...");

  float acceleration[3];
  mpl115a2.begin();

  Serial.println("Setup Finished");
  
}

void loop() {

    current_status = get_current_status(); //current_status is 0 if on the launchpad, 1 if  accellerating up, 2 if still going up but acceleration reducing, and 3 if descending
    
    //While on the Launch Pad
    while (current_status == 0) {
      //calculate vertical acceleration and set it to zero if it is negligible
      //send gps coordinates and radio pings so the rocket can be located in case of total software failure
    }
    while (current_status == 1) {
      check_airbrakes();
      
      /*calculate vertical acceleration, and calculate height and velocity from vertical acceleration
      calculate height from the barometer
      calculate averaged height and averaged velocity from the barometer and accererometer values, and use these values for the next iteration of calculations
      send gps coordinates and radio pings so the rocket can be located in case of total software failure
      */
    }
    while (current_status = 2) {
      calculate vertical acceleration, and calculate height and velocity from vertical acceleration
      calculate height from the barometer
      calculate averaged height and averaged velocity from the barometer and accererometer values, and use these values for the next iteration of calculations
      send gps coordinates and radio pings so the rocket can be located in case of total software failure
      compare current height and velocity to pre generated height/velocity curve to determine if the rocket should be braking
      make sure to save the vaules for how far open the airbrakes are at any given time, along with the height, velocity, and acceleration values
      check the weird bolts to make sure that the airbrakes are not broken
      CONSIDER ADDING SOMETHING TO MAKE SURE THE AIRBRAKES OPEN AT LEAST ONCE IN ORDER TO GATHER DATA IN CASE OF REALLY LOW FLIGHT
    }
    while (current_status = 3) {
      //Blah
    }
}
