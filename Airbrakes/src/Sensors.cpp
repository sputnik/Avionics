#include "Arduino.h"
#include "Wire.h"

#include "IMUSensor.h"
#include "PTSensor.h"

#include "Sensors.h"

// Constructor
Sensors::Sensors() {
  // the setup (not sure if this is right)
  bno = IMUSensor();
  pt = PTSensor();
}

// Deconstructor
Sensors::~Sensors() {
  //TODO
}
