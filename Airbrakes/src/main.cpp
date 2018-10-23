#define ARDUINO_MAIN
#include "Arduino.h"
#include "Data.h"

// Declarations required for Feather m0 setup
void initVariant() __attribute__((weak));
void initVariant() {}
extern "C" void __libc_init_array(void);

typedef enum State { launchPad, ascending, coasting, descending } State;

// Predefining functions used

bool switchToAscending(Data *data, int *safetyCounter);
bool switchToCoasting(Data *data, int *a_counter, int *v_counter, int *coast_safety);
bool checkSetUp();
void updateData(Data *data);
bool checkAirbreaks(Data *data);
void saveData(Data *data);

#define DATA_ARRAY_LENGTH 5

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
  Data data[DATA_ARRAY_LENGTH];
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
    if (state == coasting) {
      if (checkAirbreaks(data)) {
        state = descending;
        safetyCounter = 0;
      } // if the state is coasting
    } else if (state == ascending) {
      if (switchToCoasting(data, &a_counter, &v_counter, &coast_safety)) {
        state = coasting;
        safetyCounter = 0;
      } // if the state is ascending
    } else if (state == launchPad) {
      if (switchToAscending(data, &safetyCounter)) {
        state = ascending;
      }
    } // if the state is launchPad
    // save data to SD card no matter what
    saveData(data);

    if (millis() >= (prevTime + 1000)) {
      prevTime = millis();
      Serial.print("Time: ");
      Serial.print(data[DATA_ARRAY_LENGTH-1].time);
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
  return 0;
} // main

/**
 * Check the data of the rocket and determine if the rocket is ascending
 * @return bool true if the rocket is ascending
 *              false if the rocket is in any other states
 *
 * @param  State  data from the rocket's sensors
 */
bool switchToAscending(Data *data, int *counter){
      const double ACCELERATION_TOLERANCE = 0.0;
      const double VELOSITY_TOLERANCE = 0.0;
      const int SAFETY_TOLERANCE = 100; //define constants

      //printf("switchToAscending\n");
      double accMag = sqrt(data->accX * data->accX + data->accY * data->accY + data->accZ * data->accZ); //calculate acceleration vector mag
      double velMag = sqrt(data->accX * data->accX + data->accY * data->accY + data->accZ * data->accZ); //calculate velosity vector mag



      *counter = ( fabs((accMag - ACCELERATION_TOLERANCE)) > 0 || fabs((velMag - VELOSITY_TOLERANCE)) > 0)? *counter + 1: 0;  //update the security counter

      if (*counter >= SAFETY_TOLERANCE) return true; //return true if counter is higher than safety tolerance

      return false;
}



/**
 * Check the data of the rocket and determine if the rocket is coasting
 *
 * @return bool true if the rocket is ascending
 *              false if the tocket is in any other states
 *
 * @param State data from the rocket's sensors
 */
 /*
 *Rough draft of the conditions of switchToCoasting.
 *Planning to check current acceleration and velocity values against
 *values obtained from the data history.
 */
bool switchToCoasting(Data *data, int *a_counter, int *v_counter, int *coast_safety) {

  //check if the acceleration is less than a certain threshold, maybe -9 for gravity
  if(&data[DATA_ARRAY_LENGTH - 1] != NULL){
    if(data[DATA_ARRAY_LENGTH - 1].accZ <= -9){
      (*a_counter)++;
    } else {
      if(*a_counter - 2 > 0){
        (*a_counter)-=2;
      } else {
        *a_counter = 0;
      }
    }
  }

  //check if the last few velocity measurements are steadily decreasing
  if(&data[DATA_ARRAY_LENGTH - 1] != NULL && &data[DATA_ARRAY_LENGTH - 2] != NULL){
    if(data[DATA_ARRAY_LENGTH - 1].velZ <= data[DATA_ARRAY_LENGTH - 2].velZ){
      (*v_counter)++;
    } else {
      if(*v_counter - 1 > 0){
        (*v_counter)--;
      } else {
        *v_counter = 0;
      }
    }
  }

  if(*a_counter >= 4 || *v_counter >= 4){
    (*coast_safety)++;
    if(*coast_safety >= 5){
      return true;
    }
  } else {
    if(*coast_safety - 1 > 0){
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
  data[DATA_ARRAY_LENGTH-1].time = millis();
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
