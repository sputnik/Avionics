// Skeleton code for class file for sensor classes
// Contains implementations of all methods declared in the .h file
// Include Arduino and the header file for the class
#include "SensorSkeleton.h"
#include "SensorLibrary.h"
// Include any libraries needed for the sensor

SensorSkeleton :: SensorSkeleton(int pinUsed)
{
  theSensor = new theSensor(pinUsed);
}

void SensorSkeleton::addValue()
{
  // Since the .h creates a pointer to the object, you need "->" to access
  // its methods
  value += theSensor->getSensorValue();
}

int SensorSkeleton::getValue()
{
  return value;
}
