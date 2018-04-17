#ifndef VariableDefinitions.h
#define VariableDefinitions.h


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
#define ACTUATION_TIME  3             // Time to fully Extend the Airbrakes (seconds)

int START_ALT                 = 0;
int current_status 			= 0;

double VelocityPlot           = 0.0;
double CurrentActuationPeriod = 0.0;
double PercentOpen            = 0.0;
double ActuationTime          = 0.0;

bool AirbrakeStatus           = false;


//Defines for the GPS
//#define RXPin   6     // Software Serial RX pin
//#define TXPin   5     // Software Serial TX pin
//#define GPSBaud 9600  // Baud Rate



float adxl_altitude;
float adxl_velocity;
float bno_altitude;
float bno_velocity;
float ADXL_accel[3];  //[9]: X, [1]: Y, [2]: Z

//SD Card
File rocket_data;
#define SDCS_pin  5
char SD_data[400];
extern SDCS_pin;

// Variables/Defines for doing the Altitude Calculations (Pressure Sensor)
#define SEA_LEVEL_PRESSURE              1013.25 //Sea Level Pressure (hPa)
#define PRESSURE_AVERAGING_ITERATIONS   15      //Number of Pressure and Temperature readings to take and average


#endif