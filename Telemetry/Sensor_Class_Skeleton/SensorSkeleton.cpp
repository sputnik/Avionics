// Skeleton code for class file for sensor classes
// Contains implementations of all methods declared in the .h file
// Include Arduino and the header file for the class
#include "SensorSkeleton.h"
#include "SensorLibrary.h"
// Include any libraries needed for the sensor

// Constructor
SensorSkeleton :: SensorSkeleton(int pinUsed)
{
  // initialize the data fields
  sens = new theSensor(pinUsed);
  value = sens->getSensorValue();
} // End constructor

void SensorSkeleton::addValue()
{
  // Since the .h creates a pointer to the object, you need "->" to access
  // its methods
  value += sens->getSensorValue();
}

// Destructor
SensorSkeleton::~SensorSkeleton()
{
  // Delete any pointers
  delete sens;
} // End destructor
