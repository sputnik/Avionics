#ifndef DATA_H
# define DATA_H

struct Data {
  double accX;
  double accY;
  double accZ;
  double accV;
  double velX;
  double velY;
  double velZ;
  double velV;
  double alt;
  double pressure;
  double airbrakes;
  unsigned long t;

  /*
   * Constructor.
   *  Initializes data to default values
   */
  Data()
  {
    accX = 0.0;
    accY = 0.0;
    accZ = 0.0;
	accV = 0.0;
    velX = 0.0;
    velY = 0.0;
    velZ = 0.0;
	velV = 0.0;
    alt = 0.0;
    pressure = 0.0;
    airbrakes = 0.0;
    t = 0;
  }

  /*
   * Copy Constructor.
   * @param other
   *    The other Data object to copy into this
   */
  Data(Data& other)
  {
    accX = other.accX;
    accY = other.accY;
    accZ = other.accZ;
	accV = other.accV;
    velX = other.velX;
    velY = other.velY;
    velZ = other.velZ;
	velV = other.velV;
    alt = other.alt;
    pressure = other.pressure;
    airbrakes = other.airbrakes;
    t = other.t;
  }

  void clone(Data& other)
  {
    accX = other.accX;
    accY = other.accY;
    accZ = other.accZ;
	accV = other.accV;
    velX = other.velX;
    velY = other.velY;
    velZ = other.velZ;
	velV = other.velV;
    alt = other.alt;
    pressure = other.pressure;
    airbrakes = other.airbrakes;
    t = other.t;
  }

  void clone(Data* other)
  {
    accX = other->accX;
    accY = other->accY;
    accZ = other->accZ;
	accV = other->accV;
    velX = other->velX;
    velY = other->velY;
    velZ = other->velZ;
	velV = other->velV;
    alt = other->alt;
    pressure = other->pressure;
    airbrakes = other->airbrakes;
    t = other->t;
  }
}; // main data structure

#endif
