#include <Arduino.h>

//include all of the libraries that are needed
//#include <Wire.h>
//#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Adafruit_MPL115A2.h>
#include <Adafruit_MCP9808.h>
#include <Adafruit_ADXL345_U.h>

//include declarations for the functions that are going to be called
//formatted as follows without the "//"
// void get_pressure();
void get_BNO();


Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(1111);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Telemetry");

  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  if (!tempsensor.begin()) {
      Serial.println("Couldn't find MCP9808!");

    }

}


void loop() {
  // put your main code here, to run repeatedly:
  // code calling each function to gather the values needed
  // code to feed those values to functions that calculate altitude and velocity
  // code to send values including, altitude, velocity, acceleration, gps position, time, etc
  float time_now;
  float time_last_transmit = 0;
  time_now = millis();
  // only code for transmiting or saving data will be contained within this if
  //all other code should go before this if statement
    if (time_now > (time_last_transmit + 40)) {
      Serial.println("printing");
      get_BNO();
      time_last_transmit = time_now;
    }

    //Serial.println("wake up MCP9808.... "); // wake up MSP9808 - power consumption ~200 mikro Ampere
    //tempsensor.wake();   // wake up, ready to read!

    // Read and print out the temperature, then convert to *F
    float c = tempsensor.readTempC();
    float f = c * 9.0 / 5.0 + 32;
    Serial.print("Temp: "); Serial.print(c); Serial.print("*C\t");
    Serial.print(f); Serial.println("*F");

    //Serial.println("Shutdown MCP9808.... ");
    //tempsensor.shutdown(); // shutdown MSP9808 - power consumption ~0.1 mikro Ampere

    delay(1000);
}




void get_BNO(){

  imu::Vector<3> bnoData[4];
  bnoData[0] = bno.getVector(Adafruit_BNO055::VECTOR_EULER); // in degrees
  bnoData[1] = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  bnoData[2] = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  bnoData[3] = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);

  double vertAccel;

  for (int i = 0; i < 3; i++)
  {
    vertAccel += bnoData[2][i] + bnoData[3][i];
  } // end for

  vertAccel /= 9.81;

  String varNames[2] = {"Euler", "Acceleration"};
  String xyz[3] = {"X", "Y", "X"};

  Serial.println("BNO055:");
  Serial.println("    Vertical Acceleration:  ");
  Serial.print(vertAccel);
  for (int i = 0; i < 2; i++)
  {
    Serial.println("\t" + varNames[i]);
    for (int j = 0; j < 3; j++)
    {
      Serial.print("   " + xyz[j] + "  ");
      Serial.print(bnoData[i][j]);
    } // end for
  } // end for
} // end get_BNO


//void write_to_SD() {
//  myFile = SD.open("Telemetry.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  //if (myFile) {

    //Serial.print("Writing to Telemetry.txt...");
    //myFile.println(SD_data);
    // SD_data is a character array that is written to when the values that are to be saved on the sd card are printed with sprintf. The size of the character array limits how many characters can be printed

    // close the file:
    //myFile.close();
    //Serial.println("Telemetry.txt successfully closed.");
  //}
  //else {
    // if the file didn't open, print an error:
    //Serial.println("error opening Telemetry.txt");
  //}
