#ifndef UTIL_H
#define UTIL_H
#include "Data.h"
#include "DataHistory.h"
#include "Sensors.h"

// define constants for switch to ascending
#define ASC_ACC_TOL 0.5 // g's
#define ASC_VEL_TOL 0.0
#define ASC_ALT_TOL 0.0
#define ASC_SAFE_TOL 15
// define constants for switch to coasting
#define COAST_ACC_TOL -10.0 // m/s^2
#define COAST_VEL_TOL 0.1
#define COAST_VEL_COUNT 5
#define COAST_ACC_COUNT 5
#define COAST_TOT_COUNT 5
// constants for switch for switch to descending
#define DESCEND_VEL_TOL 0
#define DESCEND_VEL_COUNT 10
// constants of the physical rocket
#define START_HEIGHT                                                           \
  1401 // must be changed per launch location, currently SpacePort America
#define MASS_F 25.845973      // kg
#define MASS_I 36.275025      // kg
#define AREA_ROCKET .00872677 // meters squared
#define LENGTH 3.6576         // length of rocket (meters)
#define CD_ROCKET 0.42
#define GOAL_HEIGHT 9144 // meters
// constants for kalman filter
#define KALMAN_GAIN 0.5
// constants of air
#define SEA_LEVEL_PRES 101.325 // sea level pressure (KPa)
#define VISCOSITY 1.85e-5      // viscosity coefficient of air (Pa*s)
#define GAS_CONSTANT_AIR                                                       \
  287.058 // specific gas constant (R) for dry air (J/(kg*K))

namespace util {
bool switchToAscending(DataHistory *hist, int *counter);
bool switchToCoasting(DataHistory *hist, int *a_counter, int *v_counter,
                      int *safetyCounter);
bool checkAirbrakes(Sensors *sensors, DataHistory *hist, int *safetyCounter);
bool checkSetUp();
double getAltitude(double pressureKPA, double temperatureC);
double getDensity(double pressureKPA, double temperatureC);
void saveData(Data *data);
double kalman(double measurement, double prevMeasurement);
double velocityFromAlt(DataHistory *hist);
}

#endif
