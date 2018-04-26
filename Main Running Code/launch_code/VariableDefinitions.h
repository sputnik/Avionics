#ifndef VariableDefinitions.h
#define VariableDefinitions.h


//#include <Wire.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_BNO055.h>      //AMU 9-Axis orientation sensor & accelerometer
//#include <utility/imumaths.h>
//#include <Adafruit_MPL115A2.h>
//#include <TinyGPS++.h>
//#include <SD.h>

//Defines for the Air Brake Calculations
#define G               9.81          // Gravity...Duh (meters per second squared)
#define SEA_DENSITY     1.225         // Air Density at Sea Level (kg per cubic meter)
#define TIME_DELTA      0.1            // Time Between measurements (seconds)
#define AREA_ROCKET     0.0182414692  // Area of the rocket (meters squared)
#define AREA_BRAKE      0.00692       // Area of the brakes (meters squared)
#define WEIGHT_I        422.581       // Initial Weight (newtons)
#define WEIGHT_F        354.256       // Final Weight (newtons)
#define START_THRUST    2500          // Starting Thrust (newtons)
#define FUEL_BURN_RATE  14.22991494   // Weight in fuel Burned Per Unit Time (newtons per second)
#define ACTUATION_TIME  2.2             // Time to fully Extend the Airbrakes (seconds)
#define AIRBRAKE_PIN 4

int START_ALT = 32002;  //Set equal to altitude of current location
int current_status = 0;

double VelocityPlot = 0.0;
double CurrentActuationPeriod = 0.0;
double PercentOpen = 0.0;
double ActuationTime = 0.0;
bool AirbrakeStatus = false;

//RTC

//Defines for the GPS
//#define RXPin   6     // Software Serial RX pin
//#define TXPin   5     // Software Serial TX pin
//#define GPSBaud 9600  // Baud Rate

double AvgHeight          = 0;
double AvgVelocity        = 0;
double VerticalAccelBNO   = 0;
double HeightBNO          = 0;
double VelocityBNO        = 0;
double HeightPress        = 0;
double VerticalAccelADXL  = 0;
double HeightADXL         = 0;
double VelocityADXL       = 0;
double AvgHeightPrevious  = 0;

float IterationStartTime      = 0;
float IterationEndTime        = 0;
float ComputationTime         = 0;
float WaitTime               = 0;
float pressure                = 0;
float TimeAtLaunch            = 0;
float TimeSinceLaunch         = 0;
float pressureKPA             = 0;
float temperatureC            = 0;
float tempC                   = 0;
float altitude_from_pressure  = 0;
float pressure_avg_counter;

unsigned long curr_time = 0;
unsigned long old_time = 0;

bool LaunchValue = false;

//Status Lights
//TODO: "If there's any purpose, use these. If not, that's fine too."
#define Status3 10
#define Status2 9
#define Status1 5

//Linear Actuator
//TODO: "Make sure we are using these pins"
#define LA_FDBK A3
#define LA_FDBK_1 A4
#define LA_DIR 12
#define LA_PWM 11

//SD Card
#define SDCS_pin 4
char SD_data[400];

//RTC
int rtc_time[6];

// Variables/Defines for doing the Altitude Calculations (Pressure Sensor)
#define SEA_LEVEL_PRESSURE              1013.25 //Sea Level Pressure (hPa)
#define PRESSURE_AVERAGING_ITERATIONS   15      //Number of Pressure and Temperature readings to take and average


#endif
