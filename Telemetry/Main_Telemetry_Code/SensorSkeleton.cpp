// Skeleton code for class file for sensor classes
// Contains implementations of all methods declared in the .h file
// Include Arduino and the header file for the class
#include "Arduino.h"
#include "SensorSkeleton.h"
// Include any libraries needed for the sensor

SensorSkeleton :: SensorSkeleton(int pinUsed)
{
  _theSensor = new theSensor(pinUsed);
}

void addValue(int a)
{
  _value += a;
}

int getValue()
{
  return value;
}
