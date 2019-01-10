#include "math.h"
#include "utilities.hpp"

namespace util {

/**
 * Check the data of the rocket and determine if the rocket is ascending
 * @return bool true if the rocket is ascending
 *              false if the rocket is in any other states
 *
 * @param  State  data from the rocket's sensors
 */
bool switchToAscending(DataHistory *hist, int *counter) {
  int token = 0; // counter to track how many of the checks are passed  if token
                 // > 2, then the rocket is accelerating
  int arraySize = hist->getSize();

  Data *d = hist->getNewest();

  // printf("switchToAscending\n");
  double accMag = sqrt(d->accX * d->accX + d->accY * d->accY +
                       d->accZ * d->accZ); // calculate acceleration vector mag

  double velMag = sqrt(d->accX * d->accX + d->accY * d->accY +
                       d->accZ * d->accZ); // calculate velosity vector mag

  if (fabs(accMag - ASC_ACC_TOL) > 0)
    token++;
  if (fabs(velMag - ASC_VEL_TOL) > 0)
    token++;
  if (arraySize > 3 && hist->get(1)->alt - hist->get(2)->alt > ASC_ALT_TOL)
    token++; // compare values to tolerance and update token count

  (token >= 2) ? (*counter)++ : 0; // update the security counter

  if (*counter >= ASC_SAFE_TOL)
    return true; // return true if counter is higher than safety tolerance

  return false;
}

/**
 * Check the data of the rocket and determine if the rocket is coasting
 *
 * @return bool true if the rocket is coasting
 *              false if the rocket is in any other states
 *
 * @param State data from the rocket's sensors
 */
/*
Draft of switchToCoasting.
Checks the data history to see if speed has been steadily decreasing
and if acceleration is below a certain threshold.
*/
bool switchToCoasting(DataHistory *hist, int *a_counter, int *v_counter,
                      int *safetyCounter) {

  // check if the acceleration is less than a certain threshold, maybe -9 for
  // gravity
  if (hist->getNewest()->accZ <= COAST_ACC_TOL) {
    (*a_counter)++;
  } else {
    if (*a_counter - 2 > 0) {
      (*a_counter) -= 2;
    } else {
      *a_counter = 0;
    }
  }

  // check if the last few velocity measurements are steadily decreasing
  int i;
  double newer = hist->getNewest()->velZ;
  bool velcheck = false;
  for (i = 1; i < hist->getSize() / 2; i++) {
    velcheck = true;
    double older = hist->get(i)->velZ;
    if (newer > older + COAST_VEL_TOL) {
      velcheck = false;
      break;
    }
    newer = older;
  }

  if (velcheck) {
    (*v_counter)++;
  } else {
    if (*v_counter - 1 > 0) {
      (*v_counter)--;
    } else {
      *v_counter = 0;
    }
  }

  if (*a_counter >= COAST_ACC_COUNT || *v_counter >= COAST_VEL_COUNT) {
    (*safetyCounter)++;
    if (*safetyCounter >= COAST_TOT_COUNT) {
      return true;
    }
  } else {
    if (*safetyCounter - 1 > 0) {
      (*safetyCounter)--;
    } else {
      *safetyCounter = 0;
    }
  }

  return false;
}

/**
 * Calculate and deploy airbreaks
 *
 * Check if the rocket is desending
 *
 * @return bool true if the rocket is ascending
 *              false if the rocket is in any other states
 *
 * @param State data from the rocket's sensors
 *
 */
bool checkAirbrakes(DataHistory *hist, int *safetyCounter) {
  // TODO
  Data *data = hist->getNewest();
  double reynolds = (data->density) * (data->velV) * LENGTH / VISCOSITY;
  double k = .5 * data->density * CD_ROCKET * AREA_ROCKET;
  double qsquared = -1 * MASS_F * 9.81 / k;
  double hc = ((MASS_F / (2 * k)) *
               log((qsquared - (data->velV * data->velV)) / qsquared)) +
              (data->alt - START_HEIGHT);
  if (hc > GOAL_HEIGHT) {
    // actuate them bois
  }
  if (data->velV < DESCEND_VEL_TOL) {
    (*safetyCounter)++;
    if (*safetyCounter > DESCEND_VEL_COUNT) {
      return true;
    } else {
      return false;
    }
  } else {
    *safetyCounter = 0;
    return false;
  }
}

/**
 * Setup sensors used in airbrakes bay
 *
 * @return bool true if setup completed successfully
 *              false if setup failed in some way
 *
 */
bool checkSetUp() {
  // TODO
  return false;
}

/**
 * Get altitude of rocket from pressure and temperature
 *
 * @return h - altitude in km
 *
 * @param pressureKPA - pressure in KPa
 * @param temperatureC - temperature in C
 */
double getAltitude(double pressureKPA, double temperatureC) {
  // Gets altitude from pressure and temperature
  double x = SEA_LEVEL_PRES / pressureKPA;
  double y = 1 / 5.257;
  double power = pow(x, y);

  double h = ((power - 1) * (temperatureC + 273.15)) / 0.0065;
  // equation is h=(((P0/P)^(1/5.257)-1)*(T+273.15))/0.0065
  return h;
}

/**
 * Get dry air density in kg/m^3 from pressure and temperature
 *
 * @return rho - air density in kg/m^3
 *
 * @param double pressureKPA - current pressure in KPa
 * @param double temperatureC - current pressure in degrees C
 */
double getDensity(double pressureKPA, double temperatureC) {
  // WARNING: potentially inaccurate. Doesn't account for air moisture
  double press = pressureKPA * 10e-3;             // pressure in Pa
  double temp = temperatureC + 273.15;            // temp in K
  double rho = press / (GAS_CONSTANT_AIR * temp); // air density in kg/m^3
  return rho;
}

/**
 * Update data object with new sensor information
 *
 * @param sensors : The sensors object to pull data from
 * @param data : The data object to store new data in
 */
void updateData(Sensors *sensors, Data *data) {
  // TODO
  // Note: does not update data->airbrakes

  // sensor updates
  data->t = millis();
  sensors->refreshIMU();
  data->accX = sensors->getAccX(); // TODO
  data->accY = sensors->getAccY(); // TODO
  data->accZ = sensors->getAccZ(); // TODO
  data->accV = sensors->getAccV();
  data->velX = 0; // TODO
  data->velY = 0; // TODO
  data->velZ = 0; // TODO
  data->velV = 0; // TODO
  data->pressure = sensors->getPressure();
  data->temperature = sensors->getTemperature();

  // calculated values
  data->alt = getAltitude(data->pressure, data->temperature);
  data->density = getDensity(data->pressure, data->temperature);
}

/**
 * Update SD card with new sensor information
 *
 * @param data : The data to save to the SD card
 *
 */
void saveData(Data *data) {
  // TODO
}

/**
 * 1D kalman filter used to reduce signal noise
 *
 * @param double measurement - current raw measurement
 * @param double prevMeasurement - result of the previous kalman estimate
 * @param double kalmanGain - constant kalman gain coefficient
 */
double kalman(double measurement, double prevMeasurement) {
  double ret;

  ret = KALMAN_GAIN * measurement + (1 - KALMAN_GAIN) * prevMeasurement;

  return ret;
}
}
