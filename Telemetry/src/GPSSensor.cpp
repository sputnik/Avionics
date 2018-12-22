#include "GPSSensor.h"

GPSSensor::GPSSensor()
{
  gps = new TinyGPSPlus();
} // end constructor

// Returns the current date to be used as a file name
// Format: year_month_day_hour_minute
String GPSSensor::date()
{
  // Initializing the string and adding to it
  String result = String(gps->date.year()) + "_";
  result += String(gps->date.month()) + "_" + String(gps->date.day()) + "_";
  result += String(gps->time.hour()) + "_" + String(gps->time.minute());

  return result;
} // end date

// Returns the current date and time as a string
// Format: year-month-day-hour.minute.second.centisecond
String GPSSensor::dateAndTime()
{
  // Initializing the string and adding to it
  String result = String(gps->date.year()) + "-";
  result += String(gps->date.month()) + "-";
  result += String(gps->date.day()) + "-";
  result += String(gps->time.hour()) + ".";
  result += String(gps->time.minute()) + ".";
  result += String(gps->time.second()) + "." + String(gps->time.centisecond());

  return result;
} // end dateAndTime

GPSSensor::~GPSSensor()
{
  delete gps;
} // end destructor
