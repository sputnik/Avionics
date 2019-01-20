// Skeleton code for header files for sensor classes

// This checks to see if the header was already imported and will only continue
// if it wasn't to avoid any errors
#ifndef SENSORSKELETON_H_
#define SENSORSKELETON_H_

// Make sure to include the libraries needed for this sensor if you are saving data fields specific to the sensor

class SensorSkeleton
{
  // Declare any public methods
  // Methods have () at the end
  // Make sure to declare the type, e.g. int, char, void, String,...
  // Implement the methods in the .cpp file
  // The actual functions included here will be dependent on sensor
  public:
    // Constructor of the sensor object
    SensorSkeleton(int pinUsed);

    // Methods implemented within the .cpp file
    void addSomething();

    // Short methods like this can use the inline keyword to define the method
    // here as it is more time efficient
    inline int getValue()
    {
      return value;
    }

    // Destructor for the object, needed to prevent memory leak
    ~SensorSkeleton();

  // Declare any private data fields here
  // Make sure to declare the type
  private:
    // Pointer to the sensor
    // This is necessary to do because the sensor library may not have a
    // default constructor so you need a null pointer to avoid any errors
    theSensor *sens;

    // Any other needed data fields
    int value;
};

#endif
