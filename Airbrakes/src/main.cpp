#define ARDUINO_MAIN
#include "Arduino.h"
#include "Data.h"
#include "DataHistory.h"
#include "math.h"

// define constants for switch to ascending
#define ASC_ACC_TOL 0.5 // g's
#define ASC_VEL_TOL 0.0
#define ASC_ALT_TOL 0.0
#define ASC_SAFE_TOL 100
// define constants for switch to coasting
#define COAST_ACC_TOL -10.0 // m/s^2
#define COAST_VEL_TOL 5.0
#define COAST_VEL_COUNT 5
#define COAST_ACC_COUNT 5
#define COAST_TOT_COUNT 5
// constant for length of data history array
#define DATA_ARRAY_LENGTH 20
// constants for switch for switch to descending
#define DESCEND_VEL_TOL 0
#define DESCEND_VEL_COUNT 10
// constants of the physical rocket
#define START_HEIGHT 1401 //must be changed per launch location, currently SpacePort America
#define MASS_F 25.845973 // kg
#define MASS_I 36.275025 // kg
#define AREA_ROCKET .00872677 // meters squared
#define CD_ROCKET 0.42
#define GOAL_HEIGHT 9144 // meters

// Declarations required for Feather m0 setup
void initVariant() __attribute__((weak));
void initVariant() {}
extern "C" void __libc_init_array(void);

typedef enum State { launchPad, ascending, coasting, descending } State;

// Predefining functions used

bool switchToAscending(DataHistory *hist, int *safetyCounter);
bool switchToCoasting(DataHistory *hist, int *a_counter, int *v_counter,
                      int *safetyCounter);
bool checkSetUp();
void updateData(Data *data);
bool checkAirbrakes(DataHistory *hist);
void saveData(Data *data);

extern "C" char *sbrk(int i);

// Function to get the amount of ram available
int FreeRam() {
  char stack_dummy = 0;
  return &stack_dummy - sbrk(0);
}

int main() {
  // Inits required for feather m0 setup. Don't modify anything until after
  // #endif statement
  init();

  __libc_init_array();

  initVariant();

  delay(1);
#if defined(USBCON)
  USBDevice.init();
  USBDevice.attach();
#endif

  unsigned long prevTime = millis();
  // Setting up LED_BUILTIN for debugging output
  pinMode(LED_BUILTIN, OUTPUT);
  delay(100);
  Data *data = new Data;
  DataHistory *history = new DataHistory(DATA_ARRAY_LENGTH);
  State state = launchPad;

  if (!checkSetUp()) {
    Serial.println("Setup not completed correctly");
    // If stetup not completed blink LED for debugging purposes
    while (true) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
    }
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  // used to keep track of how many loops take place in one period of time.
  // for debugging purposes
  unsigned long iterationCount = 0;

  // Counters used for state changes
  int a_counter = 0;
  int v_counter = 0;
  int safetyCounter = 0;

  while (true) {
    iterationCount++;
    updateData(data);
    history->add(data);
    if (state == coasting) {
      if (checkAirbrakes(history), safetyCounter) {
        state = descending;
        safetyCounter = 0;
      } // if the state is coasting
    } else if (state == ascending) {
      if (switchToCoasting(history, &a_counter, &v_counter, &safetyCounter)) {
        state = coasting;
        safetyCounter = 0;
      } // if the state is ascending
    } else if (state == launchPad) {
      if (switchToAscending(history, &safetyCounter)) {
        state = ascending;
      }
    } // if the state is launchPad
    // save data to SD card no matter what
    saveData(data);

    if (millis() >= (prevTime + 1000)) {
      prevTime = millis();
      Serial.print("Time: ");
      Serial.print(data->t);
      Serial.print(" , iterations since last second= ");
      Serial.println(iterationCount);
      iterationCount = 0;
    } // if we want to output information
  }   // while(true)
  delete data;
  delete history;
  return 0;
} // main

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
	double k = .5 * data->density * CD_ROCKET * AREA_ROCKET;
	double qsquared = -1 * MASS_F * 9.81 / k;
	double hc = ((MASS_F / (2 * k)) * log((qsquared - (data->velV * data->velV)) / qsquared)) + (data->alt - START_HEIGHT);
	if (hc > GOAL_HEIGHT) 
	{
		//actuate them bois
	}
	if (data->velV < DESCEND_VEL_TOL)
	{
		(*safetyCounter)++;
		if (*safetyCounter > DESCEND_VEL_COUNT)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
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
 * Update data object with new sensor information
 *
 * @param data : The data object to store new data in
 *
 */
void updateData(Data *data) {
  data->t = millis();
  // TODO
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
