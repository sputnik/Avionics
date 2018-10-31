#define ARDUINO_MAIN
#include "Arduino.h"
#include "Data.h"
#include "DataHistory.h"

#define ASC_ACC_TOL 0.0
#define ASC_VEL_TOL 0.0
#define ASC_ALT_TOL 0.0
#define ASC_SAFE_TOL 100 // define constants for switch to ascending
#define DATA_ARRAY_LENGTH 10

// Declarations required for Feather m0 setup
void initVariant() __attribute__((weak));
void initVariant() {}
extern "C" void __libc_init_array(void);

typedef enum State { launchPad, ascending, coasting, descending } State;

// Predefining functions used

bool switchToAscending(DataHistory *hist, int *safetyCounter);
bool switchToCoasting(DataHistory *hist, int *a_counter, int *v_counter,
                      int *coast_safety);
bool checkSetUp();
void updateData(Data *data);
bool checkAirbreaks(DataHistory *hist);
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
  Data *data;
  DataHistory *history = new DataHistory(DATA_ARRAY_LENGTH);
  State state = launchPad;

  if (!checkSetUp()) {
    Serial.println("Setup not completed correctly");
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  int i = 0;
  // used to keep track of how many loops take place in one period of time.
  // for debugging purposes
  unsigned long iterationCount = 0;
  int a_counter = 0;
  int v_counter = 0;
  int coast_safety = 0;
  int safetyCounter = 0;

  while (true) {
    iterationCount++;
    updateData(data);
    history->add(data);
    if (state == coasting) {
      if (checkAirbreaks(history)) {
        state = descending;
        safetyCounter = 0;
      } // if the state is coasting
    } else if (state == ascending) {
      if (switchToCoasting(history, &a_counter, &v_counter, &coast_safety)) {
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
      if (i == 4) {
        Serial.print("State: ");
        Serial.println(state);
      } // if we want to print state
      i = (i + 1) % 5;
      iterationCount = 0;
    } // if we want to output information
  }   // while(true)
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
  if (arraySize > 3 && hist->get(1)->alt - hist->get(2)->alt >
      ASC_ALT_TOL)
    token++; // compare values to tolerance and update token count

  (token >= 2) ? *counter++ : 0; // update the security counter

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
                      int *coast_safety) {

  // check if the acceleration is less than a certain threshold, maybe -9 for
  // gravity
  if (hist->getNewest()->accZ <= -9) {
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
  int newer = hist->getNewest()->velZ;
  int velcheck = 0;
  for (i = 1; i < hist->getSize() / 2; i++) {
    velcheck = 1;
    int older = hist->get(i)->velZ;
    if (newer >= older + 1) {
      velcheck = 0;
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

  if (*a_counter >= 4 || *v_counter >= 4) {
    (*coast_safety)++;
    if (*coast_safety >= 5) {
      return true;
    }
  } else {
    if (*coast_safety - 1 > 0) {
      (*coast_safety)--;
    } else {
      *coast_safety = 0;
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
bool checkAirbreaks(Data *data) {
  // TODO
  return false;
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
