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
bool setup_ran = false;

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
  Serial.println("Hello!");
  setup_ran = true;

  float acceleration[3];
  mpl115a2.begin();
}

void loop() {
  if (setup_ran == true) {
    //all code goes inside here
    //----------------------------------------------------------------------------------------------------------------------------------------note: Probably want different stages in either the loop or functions to signify the difference between sitting on launch pad, heading to 10k ft, and our descent.
    //get_ADXL_data(acceleration);
    //while (we are on the pad) {
      //calculate vertical acceleration and set it to zero if it is negligible
      //send gps coordinates and radio pings so the rocket can be located in case of total software failure
    //}
    while (we are thrusting) {
      calculate vertical acceleration, and calculate height and velocity from vertical acceleration
      calculate height from the barometer
      calculate averaged height and averaged velocity from the barometer and accererometer values, and use these values for the next iteration of calculations
      send gps coordinates and radio pings so the rocket can be located in case of total software failure
    }
    while (we are ascending) {
      calculate vertical acceleration, and calculate height and velocity from vertical acceleration
      calculate height from the barometer
      calculate averaged height and averaged velocity from the barometer and accererometer values, and use these values for the next iteration of calculations
      send gps coordinates and radio pings so the rocket can be located in case of total software failure
      compare current height and velocity to pre generated height/velocity curve to determine if the rocket should be braking
      make sure to save the vaules for how far open the airbrakes are at any given time, along with the height, velocity, and acceleration values
      check the weird bolts to make sure that the airbrakes are not broken
      CONSIDER ADDING SOMETHING TO MAKE SURE THE AIRBRAKES OPEN AT LEAST ONCE IN ORDER TO GATHER DATA IN CASE OF REALLY LOW FLIGHT
    }
  }
  else {
    Serial.println("Setup did not run correctly. Running again.");
    delay(100);
    setup();
  }

}

void update_altitude_from_BNO() 
/*
 * this function gets the data from the BNO055, 
 * calculates height and velocity, 
 * and puts the results in bno_altitude and bno_velocity
 * 
 * INPUTS(global): none, have to create vectors using imu::vector
 * OUTPUTS(global): bno_altitude, bno_velocity
 */
{

}

void update_altitude_from_ADXL(float accel_vals[]) 
/*
 * this function gets the data from the ADXL, 
 * calculates height and velocity, 
 * and puts the results in adxl_altitude and adxl_velocity
 * 
 * INPUTS(global): Analog pins for x, y, and z
 * OUTPUTS(global): bno_altitude, bno_velocity
 */
{
//  int ADXL377_X_axis = analogRead(A0);
//  int ADXL377_Y_axis = analogRead(A1);
//  int ADXL377_Z_axis = analogRead(A2);
//
//  // Convert raw values to 'milli-Gs"
//  long xScaled = map(ADXL377_X_axis, 512, 517, -1000, 1000);
//  long yScaled = map(ADXL377_Y_axis, 512, 517, -1000, 1000);
//  long zScaled = map(ADXL377_Z_axis, 511, 517, -1000, 1000);
//
//  // re-scale to fractional Gs
//  float xAccel = xScaled / 1000.0;
//  float yAccel = yScaled / 1000.0;
//  float zAccel = zScaled / 1000.0;
//
//  // convert linear value and euler angles to purely vertical accel
//  // float vertical_accel = xAccel * sin( invcos( (sqrt( (xAccel * cos( euler.x ))^2 + (xAccel * cos( euler.y ))^2)/ xAccel)));
//  // height = height + (velocity * time_delta) + (.5 * vertical_accel * 9.81 * time_delta * time_delta);
//  // velocity = velocity + (vertical _accel * 9.81 * time_delta);
//
//  accel_vals[0] = xAccel;
//  accel_vals[1] = yAccel;
//  accel_vals[2] = zAccel;

}



float alt_from_pressure(float pressure, float temp)
/*
 * this function (gets), 
 * calculates (math), 
 * and puts the results in (variables)
 * 
 * INPUTS(global/internal(passed in)): 
 * OUTPUTS(global/internal(returned)): 
 */
{
  float Po = 1013.25; //Sea Level Pressure (hPa)
  float alt = 0.0;

  pressure = pressure / 10.0; //Convert to hPa

  alt = ((pow(Po / pressure, 1 / 5.257) - 1) * (temp + 273.15)) / (0.0065);

  return alt;
}
