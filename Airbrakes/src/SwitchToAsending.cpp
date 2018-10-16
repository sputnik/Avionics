#define ARDUINO_MAIN
//#include "Arduino.h"
#include <stdio.h>
#include <math.h>

//temporary file for switchToAscending for testing and debugging purposes.

typedef enum State { launchPad, ascending, coasting, descending } state;

struct Data {
  double accX ;
  double accY ;
  double accZ ;
  double velX ;
  double velY ;
  double velZ ;
  double alt ;
  double pressure ;
  double airbreaks ;
  unsigned long time;
}; // main data structure

bool switchToAscending(Data *data, int *counter);
void updateData(Data *data);

int main(){
  Data data;
  int safetycounter =0;
  while (1){
    //updateData(&data);
    switchToAscending(&data, &safetycounter);
  }

}

bool switchToAscending(Data *data, int *counter){
      const double ACCELERATION_TOLERANCE = 0.0;
      const double VELOSITY_TOLERANCE = 0.0;
      const int SAFETY_TOLERANCE = 100; //define constants

      //printf("switchToAscending\n");
      double accMag = sqrt(data->accX * data->accX + data->accY * data->accY + data->accZ * data->accZ); //calculate acceleration vector mag
      double velMag = sqrt(data->accX * data->accX + data->accY * data->accY + data->accZ * data->accZ); //calculate velosity vector mag



      *counter = ( fabs((accMag - ACCELERATION_TOLERANCE)) > 0 || fabs((velMag - VELOSITY_TOLERANCE)) > 0)? *counter + 1: 0;  //update the security counter

      if (*counter >= SAFETY_TOLERANCE) return true; //return true if counter is higher than safety tolerance

      return false;
}

/*
 * mock updateData method used to update Dada for debugging purposes
 */
void updateData(Data *data){
  scanf("%f ", data -> accX);
  scanf("%f ", data -> accY);
  scanf("%f ", data -> accZ);
  scanf("%f ", data -> velX);
  scanf("%f ", data -> velY);
  scanf("%f ", data -> velZ);
  /*scanf("%f ", data -> alt);
  scanf("%f ", data -> pressure);
  scanf("%f ", data -> airbreaks);
  data -> time ++;*/
}
