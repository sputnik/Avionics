#include "Connection.h"
#include "Data.h"
#include "DataHistory.h"
#include "Sensors.h"
#include "utilities.hpp"
#include <iostream>

// constant for length of data history array
#define DATA_ARRAY_LENGTH 20

typedef enum State { launchPad, ascending, coasting, descending } State;

int main() {
  int portnum = 8090;
  char *ip = "127.0.0.1";
  Connection c(portnum, ip);
  Sensors *sensors = new Sensors(&c);
  Data *data = new Data;
  DataHistory *history = new DataHistory(DATA_ARRAY_LENGTH);
  State state = launchPad;

  if (c.con()) {
    if (!sensors->begin()) {
      std::cout << "Setup not completed properly" << std::endl;
      sleep(3);
      return -1;
    }
  } else {
    std::cout << "Could not connect to socket" << std::endl;
    sleep(3);
    return -2;
  }

  // Counters used for state changes
  int a_counter = 0;
  int v_counter = 0;
  int safetyCounter = 0;

  while (a_counter < 5) {
    sensors->updateData(history,data);
    history->add(data);
    data->reset();
    a_counter++;
  }
  a_counter = 0;

  while (true) {
    sensors->updateData(history, data);
    history->add(data);
    if (state == coasting) {
      if (util::checkAirbrakes(sensors, history, &safetyCounter)) {
        state = descending;
        std::cout << "Switching to Descending" << std::endl;
        safetyCounter = 0;
      } // if the state is coasting
    } else if (state == ascending) {
      if (util::switchToCoasting(history, &a_counter, &v_counter,
                                 &safetyCounter)) {
        state = coasting;
        std::cout << "Switching to Coasting" << std::endl;
        safetyCounter = 0;
      } // if the state is ascending
    } else if (state == launchPad) {
      if (util::switchToAscending(history, &safetyCounter)) {
        state = ascending;
        std::cout << "Switching to Ascending" << std::endl;
      }
    } // if the state is launchPad
    // save data to SD card no matter what
    // util::saveData(data);

  } // while(true)
  delete sensors;
  delete data;
  delete history;
  return 0;
} // main
