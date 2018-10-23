#ifndef DATA_H
# define DATA_H

struct Data {
  double accX;
  double accY;
  double accZ;
  double velX;
  double velY;
  double velZ;
  double alt;
  double pressure;
  double airbreaks;
  unsigned long time;
}; // main data structure

#define DATA_ARRAY_LENGTH 5

#endif
