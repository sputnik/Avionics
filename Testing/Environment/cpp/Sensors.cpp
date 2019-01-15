#include "Sensors.h"
#include "utilities.hpp"

// Constructor
Sensors::Sensors(Connection *c) {
  con = c;
  bno = new Adafruit_BNO055(c, 0x28);
  pt = new Adafruit_MPL115A2(c);
}

union U {
  unsigned long l;
  unsigned char c[4];
};

bool Sensors::begin(void) {
  bool passed = bno->begin();
  pt->begin();
  return passed;
}

void Sensors::updateData(DataHistory* hist,Data *data) {
  refreshIMU();
  unsigned char timeReq = 0x02;
  con->sen(&timeReq, 1);
  char c[4];
  con->receive(c, 4);
  unsigned long l = 0;
  memcpy(&l, c, 4);
  data->t = l; // TODO get from environment
  float pressure;
  float temperature;
  pt->getPT(&pressure, &temperature);
  data->accX = accX;
  data->accY = accY;
  data->accZ = accZ;
  data->accV = vertAccel;
  data->velX = 0; // TODO
  data->velY = 0; // TODO
  data->velZ = 0;
  data->velV = 0;
  double verticalVel = 0;
  if (hist->getSize() > 3)
  {
    verticalVel = util::velocityFromAlt(hist);
  }
  data->velV = verticalVel;
  data->velZ  = verticalVel;
  data->pressure = pressure;
  data->temperature = temperature;
  data->alt = util::getAltitude(pressure, temperature);
  data->density = util::getDensity(pressure, temperature);
  unsigned char done = 0x01;
  con->sen(&done, 1);
}

// updates the data stored on the IMU
void Sensors::refreshIMU() {
  // TODO

  // Getting new vectors for euler angles, gravity, accelerometer, and linear
  // acceleration
  // euler = bno->getVector(Adafruit_BNO055::VECTOR_EULER);        // Unit:
  // degrees
  gravity = bno->getVector(Adafruit_BNO055::VECTOR_GRAVITY);   // Unit: m/s/s
  acc = bno->getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER); // Unit: m/s/s
  // linear = bno->getVector(Adafruit_BNO055::VECTOR_LINEARACCEL); // Unit:
  // m/s/s

  // Calculates the new vertical acceleration
  vertAccel = (gravity[0] * acc[0] + gravity[1] * acc[1] +
               gravity[2] * acc[2]) /
              9.81;

  // Linear acceleration components
  accX = acc[0];
  accY = acc[1];
  accZ = acc[2];

  // Gets the calibration for the sensor; 0 = bad, 3 = good
  // uint8_t system, gyro, accel, mag = 0;
  /*
  bno->getCalibration(&system, &gyro, &accel, &mag);
  calib[0] = system;
  calib[1] = gyro;
  calib[2] = accel;
  calib[3] = mag;*/
}

// Deconstructor
Sensors::~Sensors() {
  delete bno;
  delete pt;
  // TODO
}

void Sensors::actuateAirbrakes(void) {
  unsigned char cmd = 0X05;
  con->sen(&cmd, 1);
}

void Sensors::deActuateAirbrakes(void) {
  unsigned char cmd = 0X06;
  con->sen(&cmd, 1);
}
