#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);
  Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");
}

void loop() {
  // put your main code here, to run repeatedly:

  /* Get a new sensor event */ 
  sensors_event_t event; 
  bno.getEvent(&event);

  // Initializing the the euler angle, acceleration, linear acceleration, and gravity vectors
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  imu::Vector<3> acc = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  imu::Vector<3> linear = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  imu::Vector<3> gravity = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);

  // Calculate the vertical acceleration
  VerticalAccel = ((linear.x() * gravity.x()) + (linear.y() * gravity.y()) + (linear.z() * gravity.z())) / 9.81;

   
  /* Display the floating point data */
  // X, Y, Z Orientation
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
  Serial.println("");

  // Euler Angles
  Serial.print("BNO055:\t");
  Serial.print("Euler angles: ");
  Serial.print("X: "); 
  Serial.print(euler.x());
  Serial.print(" Y: ");
  Serial.print(euler.y());
  Serial.print(" Z: ");
  Serial.print(euler.z());
  Serial.println("");

  // Accelerometer Output in m/s^2
  Serial.print("\t\tAcceleration: ");
  Serial.print("X: "); 
  Serial.print(acc.x());
  Serial.print(" Y: ");
  Serial.print(acc.y());
  Serial.print(" Z: ");
  Serial.print(acc.z());
  Serial.println("");

  // Vertical Acceleration in m/s^2
  Serial.print("Vertical Acceleration = ")
  Serial.print(VerticalAccel);
  Serial.println("");
  
  /* Display calibration status for each sensor. 0 is bad, 3 is good */
  uint8_t system, gyro, accel, mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);
  Serial.print("CALIBRATION: Sys = ");
  Serial.print(system, DEC);
  Serial.print("Gyro = ");
  Serial.print(gyro, DEC);
  Serial.print("Accel = ");
  Serial.print(accel, DEC);
  Serial.print("Mag = ");
  Serial.println(mag, DEC);
  
  delay(100);
}
