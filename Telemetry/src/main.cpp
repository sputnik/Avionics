#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "IMUSensor.h"
#include "PTSensor.h"
#include "GPSSensor.h"
#include "RTCSensor.h"

IMUSensor bno;
PTSensor  pt;
GPSSensor gps;
RTCSensor rtc;
File data;

void setup()
{
    // put your setup code here, to run once:
    bno = IMUSensor();
    pt = PTSensor();
    gps = GPSSensor();
    rtc = RTCSensor();

    String date = gps.date() + ".txt";
    char filename[date.length()];
    date.toCharArray(filename, date.length());
    data = SD.open(filename, FILE_WRITE);
} // end setup

// Writing to the SD card
void loop()
{
  char date[gps.dateAndTime().length()];
  gps.dateAndTime().toCharArray(date, gps.dateAndTime().length());
  data.write(date);
  data.write(":\t");
  data.write("Speed: ");
  data.write(gps.speed());
  data.write(", ");
  data.write("Altitude: ");
  data.write(gps.alt());
  data.write(", ");
  data.write("Lat: ");
  data.write(gps.lat());
  data.write(", ");
  data.write("Long: ");
  data.write(gps.lng());
  data.write("\n");
} // end loop
