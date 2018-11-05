#include <Arduino.h>

//include all of the libraries that are needed
//#include <Wire.h>
//#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Adafruit_MPL115A2.h>
#include <Adafruit_MCP9808.h>
#include <Adafruit_ADXL345_U.h>
#include <RTClib.h>
#include <TinyGPS++.h>

//include declarations for the functions that are going to be called
//formatted as follows without the "//"
// void get_pressure();
void get_BNO();
void get_PT();
// void accelerometerSetup(int, int);
// void calibrateAccel(int);
void getRTC();
void getGPS();

// const int xInput = A0;
// const int yInput = A1;
// const int zInput = A2;
// const int buttonPin = 2;
//
// // Raw Ranges:
// // initialize to mid-range and allow calibration to
// // find the minimum and maximum for each axis
// int xRawMin = 512;
// int xRawMax = 512;
//
// int yRawMin = 512;
// int yRawMax = 512;
//
// int zRawMin = 512;
// int zRawMax = 512;
//
// // Take multiple samples to reduce noise
// const int sampleSize = 10;


Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
// Create the MCP9808 temperature sensor object
//Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
//Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(1111);
Adafruit_MPL115A2 pt;
RTC_DS3231 rtc;
TinyGPSPlus gps;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};



//highg declaration
const int xInput = A0;
const int yInput = A1;
const int zInput = A2;
const int buttonPin = 2;

// Raw Ranges:
// initialize to mid-range and allow calibration to
// find the minimum and maximum for each axis
int xRawMin = 512;
int xRawMax = 512;

int yRawMin = 512;
int yRawMax = 512;

int zRawMin = 512;
int zRawMax = 512;

// Take multiple samples to reduce noise
const int sampleSize = 10;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Telemetry");

  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  } // end if

  if (! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      while (1);
  }

  // if (!tempsensor.begin()) {
  //     Serial.println("Couldn't find MCP9808!");


  //  accelerometerSetup(16, 3200);//setup sensor, range and frequency
  //  calibrateAccel(1);//1 runs calibration, 0 skips, do not have to run

  analogReference(EXTERNAL);
  Serial.begin(9600);

}
 // end setup


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
      get_PT();
      getRTC();
      getGPS();
      time_last_transmit = time_now;

      // sensors_event_t accelEvent;
      // accel.getE vent(&accelEvent);
      // accelEvent.acceleration.x;

      int xRaw = ReadAxis(xInput);
        int yRaw = ReadAxis(yInput);
        int zRaw = ReadAxis(zInput);

        if (digitalRead(buttonPin) == LOW)
        {
          AutoCalibrate(xRaw, yRaw, zRaw);
        }
        else
        {
          Serial.print("Raw Ranges: X: ");
          Serial.print(xRawMin);
          Serial.print("-");
          Serial.print(xRawMax);

          Serial.print(", Y: ");
          Serial.print(yRawMin);
          Serial.print("-");
          Serial.print(yRawMax);

          Serial.print(", Z: ");
          Serial.print(zRawMin);
          Serial.print("-");
          Serial.print(zRawMax);
          Serial.println();
          Serial.print(xRaw);
          Serial.print(", ");
          Serial.print(yRaw);
          Serial.print(", ");
          Serial.print(zRaw);

          // Convert raw values to 'milli-Gs"
          long xScaled = map(xRaw, xRawMin, xRawMax, -1000, 1000);
          long yScaled = map(yRaw, yRawMin, yRawMax, -1000, 1000);
          long zScaled = map(zRaw, zRawMin, zRawMax, -1000, 1000);

          // re-scale to fractional Gs
          float xAccel = xScaled / 1000.0;
          float yAccel = yScaled / 1000.0;
          float zAccel = zScaled / 1000.0;

          Serial.print(" :: ");
          Serial.print(xAccel);
          Serial.print("G, ");
          Serial.print(yAccel);
          Serial.print("G, ");
          Serial.print(zAccel);
          Serial.println("G");


      }

      delay(1000);
    } // end if

    //Serial.println("wake up MCP9808.... "); // wake up MSP9808 - power consumption ~200 mikro Ampere
    //tempsensor.wake();   // wake up, ready to read!

    // Read and print out the temperature, then convert to *F
    // float c = tempsensor.readTempC();
    // float f = c * 9.0 / 5.0 + 32;
    // Serial.print("Temp: "); Serial.print(c); Serial.print("*C\t");
    // Serial.print(f); Serial.println("*F");

    //Serial.println("Shutdown MCP9808.... ");
    //tempsensor.shutdown(); // shutdown MSP9808 - power consumption ~0.1 mikro Ampere

    //delay(1000);



  // sensors_event_t accelEvent;
  // accel.getEvent(&accelEvent);
  // accelEvent.acceleration.x;
  // delay(100);

} // end loop

//////////////////////////////////////////////////////////////////////////////
//Function declarations



void get_BNO(){

  // Saving the data from BNO055 into an array
  imu::Vector<3> bnoData[4];
  bnoData[0] = bno.getVector(Adafruit_BNO055::VECTOR_EULER); // in degrees
  bnoData[1] = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER); // m/s/s
  bnoData[2] = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL); // m/s/s
  bnoData[3] = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY); // m/s/s

  // The vertical acceleration of the rocket in G's
  double vertAccel;

  // Calculates the vertical acceleration by dotting the linear acceleration
  // vector with the gravity vector and dividing by 9.81
  for (int i = 0; i < 3; i++)
    vertAccel += (bnoData[2][i] + bnoData[3][i])/9.81;

  // The names of the outputs and directions, for printing purposes
  String varNames[2] = {"Euler (degrees):  ", "Acceleration (m/s/s):   "};
  String xyz[3] = {"X:  ", "Y:  ", "X:  "};

  // Printing the vertical acceleration, euler angles, and acceleration
  Serial.print("\n");
  Serial.print("Vertical Acceleration (G's):  ");
  Serial.print(vertAccel);
  for (int i = 0; i < 2; i++)
  {
    Serial.print("\n");
    Serial.print(varNames[i]);
    for (int j = 0; j < 3; j++)
    {
      Serial.print(xyz[j] + "  ");
      Serial.print(bnoData[i][j]);
    } // end for
  } // end for
} // end get_BNO

void get_PT()
{
  float press = 0; // kPA
  float temp = 0; // Celsius

  // Retrieving pressure and temperature values
  pt.getPT(&press, &temp);

  // Printing pressure and temperature values
  Serial.print("\n");
  Serial.print("Pressure (kPa):    ");
  Serial.print(press,4);
  Serial.print("\n");
  Serial.print("Temperature (C):   ");
  Serial.print(temp,4);
} // end get_PT

// void accelerometerSetup(int range, int rate)
// {
// #ifndef ESP8266
//   while (!Serial);
// #endif
//   Serial.begin(9600);
//   // if(!accel.begin())
//   // {
//   //   Serial.println("Error in connecting with ADXL345 Accelerometer");
//   //   while(1);
//   // }
//   switch(range)
//   {
//     case 16:
//       accel.setRange(ADXL345_RANGE_16_G);
//       break;
//     case 8:
//       accel.setRange(ADXL345_RANGE_8_G);
//       break;
//     case 4:
//       accel.setRange(ADXL345_RANGE_4_G);
//       break;
//     case 2:
//       accel.setRange(ADXL345_RANGE_2_G);
//       break;
//     default:
//       accel.setRange(ADXL345_RANGE_16_G);
//       break;
//   }
//   switch(rate)
//   {
//     case 3200:
//       accel.setDataRate(ADXL345_DATARATE_3200_HZ);
//       break;
//     case 1600:
//       accel.setDataRate(ADXL345_DATARATE_1600_HZ);
//       break;
//     case 800:
//       accel.setDataRate(ADXL345_DATARATE_800_HZ);
//       break;
//     case 400:
//       accel.setDataRate(ADXL345_DATARATE_400_HZ);
//       break;
//     case 200:
//       accel.setDataRate(ADXL345_DATARATE_200_HZ);
//       break;
//     case 100:
//       accel.setDataRate(ADXL345_DATARATE_100_HZ);
//       break;
//     case 50:
//       accel.setDataRate(ADXL345_DATARATE_50_HZ);
//       break;
//     case 25:
//       accel.setDataRate(ADXL345_DATARATE_25_HZ);
//       break;
//     default:
//       accel.setDataRate(ADXL345_DATARATE_3200_HZ);
//       break;
//   }
//}

// void calibrateAccel(int calibrate)
// {
//   if(calibrate)
//   {
//     float AccelMinX =0;
//     float AccelMaxX =0;
//     float AccelMinY =0;
//     float AccelMaxY =0;
//     float AccelMinZ =0;
//     float AccelMaxZ =0;
//
//     for(int i=0;i<=2;i++)
//     {
//       Serial.println("Type key when ready...");
//       while (!Serial.available()){}
//
//       sensors_event_t accelTestEvent;
//       accel.getEvent(&accelTestEvent);
//
//       if (accelTestEvent.acceleration.x < AccelMinX) AccelMinX = accelTestEvent.acceleration.x;
//       if (accelTestEvent.acceleration.x > AccelMaxX) AccelMaxX = accelTestEvent.acceleration.x;
//
//       if (accelTestEvent.acceleration.y < AccelMinY) AccelMinY = accelTestEvent.acceleration.y;
//       if (accelTestEvent.acceleration.y > AccelMaxY) AccelMaxY = accelTestEvent.acceleration.y;
//
//       if (accelTestEvent.acceleration.z < AccelMinZ) AccelMinZ = accelTestEvent.acceleration.z;
//       if (accelTestEvent.acceleration.z > AccelMaxZ) AccelMaxZ = accelTestEvent.acceleration.z;
//
//       Serial.print("Accel Minimums: "); Serial.print(AccelMinX); Serial.print("  ");Serial.print(AccelMinY); Serial.print("  "); Serial.print(AccelMinZ); Serial.println();
//       Serial.print("Accel Maximums: "); Serial.print(AccelMaxX); Serial.print("  ");Serial.print(AccelMaxY); Serial.print("  "); Serial.print(AccelMaxZ); Serial.println();
//
//       while (Serial.available())
//       {
//         Serial.read();  // clear the input buffer
//       }
//     }
//   }
// } // end claibrateAccel

void getRTC()
{
  DateTime now = rtc.now();

  Serial.print("\n");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
} // end getRTC

void getGPS()
{
  Serial.println(gps.satellites.isValid());
} // end getGPS
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


  //
  // Read "sampleSize" samples and report the average
  //
  int ReadAxis(int axisPin)
  {
    long reading = 0;
    analogRead(axisPin);
    delay(1);
    for (int i = 0; i < sampleSize; i++)
    {
      reading += analogRead(axisPin);
    }
    return reading/sampleSize;
  }

  //
  // Find the extreme raw readings from each axis
  //
  void AutoCalibrate(int xRaw, int yRaw, int zRaw)
  {
    Serial.println("Calibrate");
    if (xRaw < xRawMin)
    {
      xRawMin = xRaw;
    }
    if (xRaw > xRawMax)
    {
      xRawMax = xRaw;
    }

    if (yRaw < yRawMin)
    {
      yRawMin = yRaw;
    }
    if (yRaw > yRawMax)
    {
      yRawMax = yRaw;
    }

    if (zRaw < zRawMin)
    {
      zRawMin = zRaw;
    }
    if (zRaw > zRawMax)
    {
      zRawMax = zRaw;
    }
  }
