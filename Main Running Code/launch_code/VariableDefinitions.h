#ifndef VariableDefinitions.h
#define VariableDefinitions.h


#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>      //AMU 9-Axis orientation sensor & accelerometer
#include <utility/imumaths.h>
#include <Adafruit_MPL115A2.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SD.h>

//Defines for the Air Brake Calculations
#define G               9.81          // Gravity...Duh (meters per second squared)
#define SEA_DENSITY     1.225         // Air Density at Sea Level (kg per cubic meter)
#define TIME_DELTA      0.01          // Time Between measurements (seconds)
#define AREA_ROCKET     0.0182414692  // Area of the rocket (meters squared)
#define AREA_BRAKE      0.00692       // Area of the brakes (meters squared)
#define WEIGHT_I        422.581       // Initial Weight (newtons)
#define WEIGHT_F        354.256       // Final Weight (newtons)
#define START_THRUST    2500          // Starting Thrust (newtons)
#define FUEL_BURN_RATE  14.22991494   // Weight in fuel Burned Per Unit Time (newtons per second)
#define ACTUATION_TIME  2.2             // Time to fully Extend the Airbrakes (seconds)
#define AIRBRAKE_PIN 4

int START_ALT = 0;
int current_status = 0;

double VelocityPlot = 0.0;
double CurrentActuationPeriod = 0.0;
double PercentOpen = 0.0;
double ActuationTime = 0.0;
bool AirbrakeStatus = false;

//RTC
RTC_DS3231 rtc;

//Defines for the GPS
//#define RXPin   6     // Software Serial RX pin
//#define TXPin   5     // Software Serial TX pin
//#define GPSBaud 9600  // Baud Rate

//function declarations
void check_airbrakes();
void get_Alt_BNO();
float get_Alt_Pressure();
void get_Accel_ADXL();
void get_Avg_Alt();
void write_to_SD(char SD_info[]);
int get_current_status();
void while_on_pad();
void while_launching();
void while_still_rising();
void while_descending();

double AvgHeight = 0;
double AvgVelocity;
double VerticalAccelBNO;
bool LaunchValue = false;
double HeightBNO;
double VelocityBNO;
double HeightPress;
double VerticalAccelADXL;
double HeightADXL;
double VelocityADXL;
double AvgHeightPrevious = 0;
float IterationStartTime;
float IterationEndTime;
float ComputationTime;
float WaitTime;
float pressure;


//SD Card
File rocket_data;
#define SDCS_pin 5
char SD_data[400];

// Variables/Defines for doing the Altitude Calculations (Pressure Sensor)
#define SEA_LEVEL_PRESSURE              1013.25 //Sea Level Pressure (hPa)
#define PRESSURE_AVERAGING_ITERATIONS   15      //Number of Pressure and Temperature readings to take and average


#endif
