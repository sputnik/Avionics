// Skeleton code for header files for sensor classes

// This checks to see if the header was already imported and will only continue
// if it wasn't to avoid any errors
#ifndef SENSORSKELETON_H_
#define SENSORSKELETON_H_
#include "Arduino.h"
// Make sure to include the libraries needed for this sensor

class SensorSkeleton
{
  // Declare any public methods and variables here
  // Methods have () at the end
  // Make sure to declare the type, e.g. int, char, void, String,...
  // Implement the methods in the .cpp file
  // The actual functions included here will be dependent on sensor
  public:
    // Instances of the sensor
    // This is necessary to do because the sensor library may not have a
    // default constructor so you need a null pointer to avoid any errors
    theSensor sens;
    theSensor *pointer = sens;
    pointer = NULL;

    // Any other needed data fields
    int value;

    // Constructor of the sensor object
    SensorSkeleton(int pinUsed);

    // Methods implemented within the .cpp file
    void addSomething(int a);
    int getValue();
};

#endif
