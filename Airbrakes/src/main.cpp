#define ARDUINO_MAIN
#include "Arduino.h"

// Declarations required for Feather m0 setup
void initVariant() __attribute__((weak));
void initVariant() {}
extern "C" void __libc_init_array(void);

typedef enum State { launchPad, ascending, coasting, descending } State;

struct Data {
  double accX = 0.0;
  double accY = 0.0;
  double accZ = 0.0;
  double velX = 0.0;
  double velY = 0.0;
  double velZ = 0.0;
  double alt = 0.0;
  double pressure = 0.0;
  double airbreaks = 0.0;
  unsigned long time = 0;
}; // main data structure

// Predefining functions used
bool switchToAscending(Data *data);
bool switchToCoasting(Data *data);
bool checkSetUp();
void updateData(Data *data);
bool checkAirbreaks(Data *data);
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

  Data data;
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

  while (true) {
    iterationCount++;
    updateData(&data);
    if (state == coasting) {
      if (checkAirbreaks(&data)) {
        state = descending;
      } // if the state is coasting
    } else if (state == ascending) {
      if (switchToCoasting(&data)) {
        state = coasting;
      } // if the state is ascending
    } else if (state == launchPad) {
      if (switchToAscending(&data)) {
        state = ascending;
      }
    } // if the state is launchPad
    // save data to SD card no matter what
    saveData(&data);
    double a = iterationCount * iterationCount * iterationCount;

    if (millis() >= (prevTime + 1000)) {
      prevTime = millis();
      Serial.print("Time: ");
      Serial.print(data.time);
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
bool switchToAscending(Data *data) {
  // TODO
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
bool switchToCoasting(Data *data) {
  // TODO
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
  data->time = millis();
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
