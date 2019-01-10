#define ARDUINO_MAIN
#include "Arduino.h"
#include "Data.h"
#include "DataHistory.h"
#include "IMUSensor.h"
#include "PTSensor.h"
#include "Sensors.h"
#include "utilities.hpp"

// constant for length of data history array
#define DATA_ARRAY_LENGTH 20

// Declarations required for Feather m0 setup
void initVariant() __attribute__((weak));
void initVariant() {}
extern "C" void __libc_init_array(void);

typedef enum State { launchPad, ascending, coasting, descending } State;

// Predefining functions used
/*
bool switchToAscending(DataHistory *hist, int *safetyCounter);
bool switchToCoasting(DataHistory *hist, int *a_counter, int *v_counter,
                      int *safetyCounter);
bool checkSetUp();
void updateData(Data *data);
bool checkAirbrakes(DataHistory *hist);
void saveData(Data *data);

double kalman(double measurement, double prevMeasurement);
*/
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
  Sensors *sensors = new Sensors;
  Data *data = new Data;
  DataHistory *history = new DataHistory(DATA_ARRAY_LENGTH);
  State state = launchPad;

  if (!util::checkSetUp()) {
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
    util::updateData(sensors, data);
    history->add(data);
    if (state == coasting) {
      if (util::checkAirbrakes(history, &safetyCounter)) {
        state = descending;
        safetyCounter = 0;
      } // if the state is coasting
    } else if (state == ascending) {
      if (util::switchToCoasting(history, &a_counter, &v_counter,
                                 &safetyCounter)) {
        state = coasting;
        safetyCounter = 0;
      } // if the state is ascending
    } else if (state == launchPad) {
      if (util::switchToAscending(history, &safetyCounter)) {
        state = ascending;
      }
    } // if the state is launchPad
    // save data to SD card no matter what
    util::saveData(data);

    if (millis() >= (prevTime + 1000)) {
      prevTime = millis();
      Serial.print("Time: ");
      Serial.print(data->t);
      Serial.print(" , iterations since last second= ");
      Serial.println(iterationCount);
      iterationCount = 0;
    } // if we want to output information
  }   // while(true)
  delete sensors;
  delete data;
  delete history;
  return 0;
} // main
