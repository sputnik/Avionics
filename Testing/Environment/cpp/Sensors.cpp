#include "Sensors.h"
#include "utilities.hpp"

// Constructor
Sensors::Sensors(Connection *c) {
  con = c;
  bno = new Adafruit_BNO055(c, 0x28);
  pt = new Adafruit_MPL115A2(c);
}

bool Sensors::begin(void) {
  bool passed = bno->begin();
  pt->begin();
  return passed;
}

void Sensors::updateData(Data *data) {
  refreshIMU();
  data->t = 0; // TODO get from environment
  float pressure;
  float temperature;
  pt->getPT(&pressure, &temperature);
  data->accX = accX; // TODO
  data->accY = accY; // TODO
  data->accZ = accZ; // TODO
  data->accV = vertAccel;
  data->velX = 0; // TODO
  data->velY = 0; // TODO
  data->velZ = 0; // TODO
  data->velV = 0; // TODO
  data->pressure = pressure;
  data->temperature = temperature;
  data->alt = util::getAltitude(pressure, temperature);
  data->density = util::getDensity(pressure, temperature);
  // TODO tell environment we're done asking this iteration
}

// updates the data stored on the IMU
void Sensors::refreshIMU() {
  // TODO

  // Getting new vectors for euler angles, gravity, accelerometer, and linear
  // acceleration
  euler = bno->getVector(Adafruit_BNO055::VECTOR_EULER);        // Unit: degrees
  gravity = bno->getVector(Adafruit_BNO055::VECTOR_GRAVITY);    // Unit: m/s/s
  acc = bno->getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);  // Unit: m/s/s
  linear = bno->getVector(Adafruit_BNO055::VECTOR_LINEARACCEL); // Unit: m/s/s

  // Calculates the new vertical acceleration
  vertAccel = (gravity[0] * linear[0] + gravity[1] * linear[1] +
               gravity[2] * linear[2]) /
              9.81;

  // Linear acceleration components
  accX = linear[0];
  accY = linear[1];
  accZ = linear[2];

  // Gets the calibration for the sensor; 0 = bad, 3 = good
  uint8_t system, gyro, accel, mag = 0;
  bno->getCalibration(&system, &gyro, &accel, &mag);
  calib[0] = system;
  calib[1] = gyro;
  calib[2] = accel;
  calib[3] = mag;
}

// Deconstructor
Sensors::~Sensors() {
  delete bno;
  delete pt;
  // TODO
}

void Sensors::actuateAirbrakes(void) {
  // TODO, send message to environment
}

void Sensors::deActuateAirbrakes(void) {
  // TODO, send msg to env
}
