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
      return 1;
    }
  } else {
    std::cout << "Could not connect to socket. Retrying 5 times." << std::endl;
    sleep(3);
    for (int i = 1; i <= 5; i++) {
      if (c.con()) {
        break;
      } else {
        std::cout << "Attempt = " << i << std::endl;
        sleep(2);
      }
    }
    if (!c.connected()) {
      return 2;
    }
  }

  // Counters used for state changes
  int a_counter = 0;
  int v_counter = 0;
  int safetyCounter = 0;

  for (int i = 0; i < 5; i++) {
    sensors->updateData(history, data);
    history->add(data);
  }
  bool flying = true;
  while (flying) {
    data->reset();
    sensors->updateData(history, data);
    if (state == descending && data->alt <= START_HEIGHT) {
      flying = false;
      std::cout << "On ground" << std::endl;
    }
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
  sleep(2);
  return 0;
} // main
