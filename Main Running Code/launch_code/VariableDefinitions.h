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
#define TIME_DELTA      0.1            // Time Between measurements (seconds)
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
float Wait_Time               = 0;
float pressure                = 0;
float TimeAtLaunch            = 0;
float TimeSinceLaunch         = 0;
float pressureKPA             = 0;
float temperatureC            = 0;
float tempC                   = 0;
float altitude_from_pressure  = 0;

bool LaunchValue = false;

//Status Lights
#define Status4 11
#define Status3 10
#define Status2 9
#define Status1 5

//Linear Actuator
#define LA_FDBK_0 A3
#define LA_FDBK_1 A4

//SD Card
File rocket_data;
#define SDCS_pin 5
char SD_data[400];

//RTC
int rtc_Second = 0;
int rtc_Minute = 0;
int rtc_Hour = 0;
int rtc_Day = 0;
int rtc_Month = 0;
int rtc_Year = 0; 

// Variables/Defines for doing the Altitude Calculations (Pressure Sensor)
#define SEA_LEVEL_PRESSURE              1013.25 //Sea Level Pressure (hPa)
#define PRESSURE_AVERAGING_ITERATIONS   15      //Number of Pressure and Temperature readings to take and average


#endif